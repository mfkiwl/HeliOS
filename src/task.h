/**
 * @file task.h
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel sources for task management
 * @version 0.3.5
 * @date 2022-01-31
 *
 * @copyright
 * HeliOS Embedded Operating System
 * Copyright (C) 2020-2023 Manny Peterson <mannymsp@gmail.com>
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
#ifndef TASK_H_
#define TASK_H_

#include "config.h"
#include "defines.h"
#include "types.h"
#include "port.h"
#include "device.h"
#include "mem.h"
#include "queue.h"
#include "stream.h"
#include "sys.h"
#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif

Task_t *xTaskCreate(const Char_t *name_, void (*callback_)(Task_t *task_, TaskParm_t *parm_), TaskParm_t *taskParameter_);
void xTaskDelete(const Task_t *task_);
Task_t *xTaskGetHandleByName(const Char_t *name_);
Task_t *xTaskGetHandleById(const Base_t id_);
TaskRunTimeStats_t *xTaskGetAllRunTimeStats(Base_t *tasks_);
TaskRunTimeStats_t *xTaskGetTaskRunTimeStats(const Task_t *task_);
Base_t xTaskGetNumberOfTasks(void);
TaskInfo_t *xTaskGetTaskInfo(const Task_t *task_);
TaskInfo_t *xTaskGetAllTaskInfo(Base_t *tasks_);
TaskState_t xTaskGetTaskState(const Task_t *task_);
Char_t *xTaskGetName(const Task_t *task_);
Base_t xTaskGetId(const Task_t *task_);
void xTaskNotifyStateClear(Task_t *task_);
Base_t xTaskNotificationIsWaiting(const Task_t *task_);
Base_t xTaskNotifyGive(Task_t *task_, const Base_t notificationBytes_, const Char_t *notificationValue_);
TaskNotification_t *xTaskNotifyTake(Task_t *task_);
void xTaskResume(Task_t *task_);
void xTaskSuspend(Task_t *task_);
void xTaskWait(Task_t *task_);
void xTaskChangePeriod(Task_t *task_, const Ticks_t timerPeriod_);
Ticks_t xTaskGetPeriod(const Task_t *task_);
void xTaskResetTimer(Task_t *task_);
void xTaskStartScheduler(void);
void xTaskResumeAll(void);
void xTaskSuspendAll(void);
SchedulerState_t xTaskGetSchedulerState(void);
void xTaskChangeWDPeriod(Task_t *task_, const Ticks_t wdTimerPeriod_);
Ticks_t xTaskGetWDPeriod(const Task_t *task_);

#if defined(POSIX_ARCH_OTHER)
void __TaskStateClear__(void);
#endif

#ifdef __cplusplus
}
#endif
#endif