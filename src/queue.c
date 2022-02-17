/**
 * @file queue.c
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel sources for message queues
 * @version 0.3.0
 * @date 2022-01-31
 *
 * @copyright
 * HeliOS Embedded Operating System
 * Copyright (C) 2020-2022 Manny Peterson <mannymsp@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "queue.h"

extern SysFlags_t sysFlags;

/* The xQueueCreate() system call creates a message queue for inter-task
communication. */
Queue_t *xQueueCreate(Base_t limit_) {
  Queue_t *ret = NULL;

  SYSASSERT(limit_ >= CONFIG_QUEUE_MINIMUM_LIMIT);

  /* Check to make sure the limit parameter is greater than or equal to the
  setting CONFIG_QUEUE_MINIMUM_LIMIT. */
  if (limit_ >= CONFIG_QUEUE_MINIMUM_LIMIT) {
    ret = (Queue_t *)xMemAlloc(sizeof(Queue_t));

    SYSASSERT(ISNOTNULLPTR(ret));

    /* Check if queue was successfully allocated by xMemAlloc(). */
    if (ISNOTNULLPTR(ret)) {
      ret->length = zero;

      ret->limit = limit_;

      ret->head = NULL;

      ret->tail = NULL;
    }
  }

  return ret;
}

/* The xQueueDelete() system call will delete a queue created by xQueueCreate(). xQueueDelete()
will delete a queue regardless of how many messages the queue contains at the time xQueueDelete() is called. */
void xQueueDelete(Queue_t *queue_) {

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is null */
  if (ISNOTNULLPTR(queue_)) {
    /* If the queue has a head it contains messages, iterate through the queue and drop
    all of the messages. */
    while (ISNOTNULLPTR(queue_->head)) {
      xQueueDropMessage(queue_);
    }

    xMemFree(queue_);
  }

  return;
}

/* The xQueueGetLength() system call returns the length of the queue (the number of messages
the queue currently contains). */
Base_t xQueueGetLength(Queue_t *queue_) {
  Base_t ret = zero;

  Base_t messages = zero;

  Message_t *messageCursor = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is not null. */
  if (ISNOTNULLPTR(queue_)) {
    messageCursor = queue_->head;

    /* If the queue has a head, iterate through the queue and count the number of messages. */
    while (ISNOTNULLPTR(messageCursor)) {
      messages++;

      messageCursor = messageCursor->next;
    }

    SYSASSERT(queue_->length == messages);

    /* Check to make sure the number of messages counted matches the length attribute of the queue.
    This is to confirm the integrity of the queue before returning its length. */
    if (queue_->length == messages) {
      ret = messages;
    }
  }

  return ret;
}

/* The xQueueIsEmpty() system call will return a true or false dependent on whether the queue is
empty or contains one or more messages. */
Base_t xQueueIsQueueEmpty(Queue_t *queue_) {
  Base_t ret = false;

  Base_t messages = zero;

  Message_t *messageCursor = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue pointer is not null. */
  if (ISNOTNULLPTR(queue_)) {
    messageCursor = queue_->head;

    /* If the queue has a head, iterate through the queue and count the number of messages. */
    while (ISNOTNULLPTR(messageCursor)) {
      messages++;

      messageCursor = messageCursor->next;
    }

    SYSASSERT(queue_->length == messages);

    /* Check to make sure the number of messages counted matches the length attribute of the queue
    and if the number of messages equals zero. */
    if ((messages == zero) && (queue_->length == messages)) {
      ret = true;
    }
  }

  return ret;
}

/* The xQueueIsFull() system call will return a true or false dependent on whether the queue is
full or contains zero messages. A queue is considered full if the number of messages in the queue
is equal to the queue's length limit. */
Base_t xQueueIsQueueFull(Queue_t *queue_) {
  Base_t ret = false;

  Base_t messages = zero;

  Message_t *messageCursor = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is not null. */
  if (ISNOTNULLPTR(queue_)) {
    messageCursor = queue_->head;

    /* If the queue has a head, iterate through the queue and count the number of messages. */
    while (ISNOTNULLPTR(messageCursor)) {
      messages++;

      messageCursor = messageCursor->next;
    }

    SYSASSERT(queue_->length == messages);

    /* Check to make sure the number of messages counted matches the length attribute of the queue
    and if the number of messages is greater than or equal to the queue length limit. */
    if ((messages >= queue_->limit) && (queue_->length == messages)) {
      ret = true;
    }
  }

  return ret;
}

/* The xQueueMessageWaiting() system call returns true or false dependent on whether
there is at least one message waiting. The queue does not have to be full to return true. */
Base_t xQueueMessagesWaiting(Queue_t *queue_) {
  Base_t ret = false;

  Base_t messages = zero;

  Message_t *messageCursor = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is not null. */
  if (ISNOTNULLPTR(queue_)) {
    messageCursor = queue_->head;

    /* If the queue has a head, iterate through the queue and count the number of messages. */
    while (ISNOTNULLPTR(messageCursor)) {
      messages++;

      messageCursor = messageCursor->next;
    }

    SYSASSERT(queue_->length == messages);

    /* Check to make sure the number of messages counted matches the length attribute of the queue
    and if the number of messages is greater than zero. */
    if ((messages > zero) && (queue_->length == messages)) {
      ret = true;
    }
  }

  return ret;
}

/* The xQueueSend() system call will send a message to the queue. The size of the message
value is passed in the message bytes parameter. */
Base_t xQueueSend(Queue_t *queue_, Base_t messageBytes_, const char *messageValue_) {
  Base_t ret = false;

  Message_t *message = NULL;

  Base_t messages = zero;

  Message_t *messageCursor = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  SYSASSERT(messageBytes_ > zero);

  SYSASSERT(messageBytes_ <= CONFIG_MESSAGE_VALUE_BYTES);

  SYSASSERT(ISNOTNULLPTR(messageValue_));

  /* Check if the queue parameter is not null, message bytes is between one and CONFIG_MESSAGE_VALUE_BYTES and the message value parameter
  is not null. */
  if ((ISNOTNULLPTR(queue_)) && (messageBytes_ > zero) && (messageBytes_ <= CONFIG_MESSAGE_VALUE_BYTES) && (ISNOTNULLPTR(messageValue_))) {
    messageCursor = queue_->head;

    /* If the queue has a head, iterate through the queue and count the number of messages. */
    while (ISNOTNULLPTR(messageCursor)) {
      messages++;

      messageCursor = messageCursor->next;
    }

    SYSASSERT(queue_->length == messages);

    /* Check if the length of the queue is less than the limit and the length of the queue matches the number of messages
    counted. */
    if ((queue_->length < queue_->limit) && (queue_->length == messages)) {
      message = (Message_t *)xMemAlloc(sizeof(Message_t));

      SYSASSERT(ISNOTNULLPTR(message));

      /* Check if the message was successfully allocated by xMemAlloc(). */
      if (ISNOTNULLPTR(message)) {
        message->messageBytes = messageBytes_;

        memcpy_(message->messageValue, messageValue_, CONFIG_MESSAGE_VALUE_BYTES);

        message->next = NULL;

        /* If the queue tail is not null then it already contains messages and append the new message, otherwise
        set the head and tail to the new message. */
        if (ISNOTNULLPTR(queue_->tail)) {
          queue_->tail->next = message;

          queue_->tail = message;

        } else {
          queue_->head = message;

          queue_->tail = message;
        }

        queue_->length++;

        ret = true;
      }
    }
  }

  return ret;
}

/* The xQueuePeek() system call will return the next message in the queue without
dropping the message. */
QueueMessage_t *xQueuePeek(Queue_t *queue_) {
  QueueMessage_t *ret = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is not null. */
  if (ISNOTNULLPTR(queue_)) {
    /* Check if the head of the queue is not null. */
    if (ISNOTNULLPTR(queue_->head)) {
      ret = (QueueMessage_t *)xMemAlloc(sizeof(QueueMessage_t));

      SYSASSERT(ISNOTNULLPTR(ret));

      /* Check if a new message was successfully allocated by xMemAlloc(). */
      if (ISNOTNULLPTR(ret)) {
        ret->messageBytes = queue_->head->messageBytes;

        memcpy_(ret->messageValue, queue_->head->messageValue, CONFIG_MESSAGE_VALUE_BYTES);
      }
    }
  }

  return ret;
}

/* The xQueueDropMessage() system call will drop the next message from the queue without
returning the message. */
void xQueueDropMessage(Queue_t *queue_) {
  Message_t *message = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is not null. */
  if (ISNOTNULLPTR(queue_)) {
    /* Check if the head of the queue is null, if so
    return because there is nothing to drop. */
    if (ISNOTNULLPTR(queue_->head)) {
      message = queue_->head;

      queue_->head = queue_->head->next;

      /* Again check if the head of the queue is null, if so set the tail
      of the queue to null. */
      if (ISNULLPTR(queue_->head)) {
        queue_->tail = NULL;
      }

      queue_->length--;

      xMemFree(message);
    }
  }

  return;
}

/* The xQueueReceive() system call will return the next message in the queue and drop
it from the queue. */
QueueMessage_t *xQueueReceive(Queue_t *queue_) {
  QueueMessage_t *ret = NULL;

  SYSASSERT(ISNOTNULLPTR(queue_));

  /* Check if the queue parameter is not null. */
  if (ISNOTNULLPTR(queue_)) {
    ret = xQueuePeek(queue_);

    /* Check if the message returned from xQueuePeek() is not null. If so, drop the message from the
    queue and return the message. */
    if (ISNOTNULLPTR(ret)) {
      xQueueDropMessage(queue_);
    }
  }

  return ret;
}