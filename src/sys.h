/**
 * @file sys.h
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel sources system related calls
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
#ifndef SYS_H_
#define SYS_H_

#include "config.h"
#include "defines.h"
#include "types.h"
#include "port.h"
#include "device.h"
#include "mem.h"
#include "queue.h"
#include "stream.h"
#include "task.h"
#include "timer.h"

extern SysFlags_t sysFlags;

#ifdef __cplusplus
extern "C" {
#endif

void __SystemAssert__(const char *file_, const int line_);
void xSystemInit(void);
void xSystemHalt(void);
SystemInfo_t *xSystemGetSystemInfo(void);

#if defined(CONFIG_ENABLE_ARDUINO_CPP_INTERFACE)
void __ArduinoAssert__(const char *file_, int line_);
#endif

#if defined(POSIX_ARCH_OTHER)
void __SysStateClear__(void);
#endif

#ifdef __cplusplus
}
#endif
#endif