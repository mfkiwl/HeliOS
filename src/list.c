/*
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
 */

#include "list.h"

volatile TaskListItem_t *taskListHead;
volatile TaskListItem_t *taskListTail;
volatile TaskListItem_t *taskListPrev;
volatile TaskListItem_t *taskListCurr;
volatile TaskListItem_t *taskListPrevPriv;
volatile TaskListItem_t *taskListCurrPriv;

void TaskListInit() {
  taskListHead = null;
  taskListTail = null;
  taskListPrev = null;
  taskListCurr = null;
  taskListPrevPriv = null;
  taskListCurrPriv = null;
  TaskListRewind();
  TaskListRewindPriv();
}

void TaskListClear() {
  while (taskListHead)
    TaskListRemove();
}

void TaskListAdd(Task_t *task_) {
  TaskListItem_t *item = (TaskListItem_t *)xMemAlloc(sizeof(TaskListItem_t));

  if (item && task_) {
    item->task = task_;
    item->next = null;
    if (taskListHead) {
      taskListTail->next = item;
      taskListTail = item;
      TaskListRewind();
      TaskListRewindPriv();
    } else {
      taskListHead = item;
      taskListTail = item;
      TaskListRewind();
      TaskListRewindPriv();
    }
  }
}

void TaskListRemove() {
  if (taskListCurr) {
    if (taskListCurr == taskListHead && taskListCurr == taskListTail) {
      TaskListItem_t *item = (TaskListItem_t *)taskListHead;
      TaskListInit();
      xMemFree(item->task);
      xMemFree(item);
    } else if (taskListCurr == taskListHead) {
      TaskListItem_t *item = (TaskListItem_t *)taskListHead;
      taskListHead = taskListHead->next;
      TaskListRewind();
      TaskListRewindPriv();
      xMemFree(item->task);
      xMemFree(item);
    } else if (taskListCurr == taskListTail) {
      TaskListItem_t *item = (TaskListItem_t *)taskListTail;
      taskListTail = taskListPrev;
      taskListPrev->next = null;
      TaskListRewind();
      TaskListRewindPriv();
      xMemFree(item->task);
      xMemFree(item);
    } else {
      TaskListItem_t *item = (TaskListItem_t *)taskListCurr;
      taskListPrev->next = taskListCurr->next;
      TaskListRewind();
      TaskListRewindPriv();
      xMemFree(item->task);
      xMemFree(item);
    }
  }
}

Task_t *TaskListGet() {
  if (taskListCurr)
    return taskListCurr->task;
  return null;
}

Task_t *TaskListGetPriv() {
  if (taskListCurrPriv)
    return taskListCurrPriv->task;
  return null;
}

bool TaskListMoveNext() {
  if (taskListCurr) {
    if (taskListCurr->next) {
      taskListPrev = taskListCurr;
      taskListCurr = taskListCurr->next;
      return true;
    }
  }
  return false;
}

bool TaskListMoveNextPriv() {
  if (taskListCurrPriv) {
    if (taskListCurrPriv->next) {
      taskListPrevPriv = taskListCurrPriv;
      taskListCurrPriv = taskListCurrPriv->next;
      return true;
    }
  }
  return false;
}

void TaskListRewind() {
  taskListPrev = null;
  taskListCurr = taskListHead;
}

void TaskListRewindPriv() {
  taskListPrevPriv = null;
  taskListCurrPriv = taskListHead;
}