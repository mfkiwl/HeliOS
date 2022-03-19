/**
 * @file defines.h
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel header for macros and definitions
 * @version 0.3.3
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
#ifndef DEFINES_H_
#define DEFINES_H_

#include <limits.h>
#include <stdint.h>

#define OTHER_ARCH_DEBUG

/* Check that the system HeliOS is being targeted for has an
8-bit wide byte. */
#if !defined(CHAR_BIT)
#pragma message("WARNING: Unable to determine if system has an 8-bit wide byte. CHAR_BIT not defined?")
#else
#if CHAR_BIT != 8
#pragma message("WARNING: System may not have an 8-bit wide byte!")
#endif
#endif



/* Definition blocks for embedded platform and/or tool-chain
specific headers and functions to compile and run HeliOS. When a
new embedded platform and/or tool-chain is added, the following
defines (with the exception of CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS) must
be included:

* CURRENTTIME()
* DISABLE_INTERRUPTS()
* ENABLE_INTERRUPTS()
* TIME_T_TYPE
* CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS <- Optional. However, if defined
  must be enclosed in an #if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
  block.

If no definition block for the embedded platform and/or tool-chain
is matched, the "else" block will print a compiler warning and attempt
to default to the Arduino platform and/or tool-chain. */
#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x20u /* 32u */
#endif


#elif defined(ARDUINO_ARCH_SAM)

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x80u /* 128u */
#endif



#elif defined(ARDUINO_ARCH_SAMD)

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x80u /* 128u */
#endif



#elif defined(ARDUINO_ARCH_ESP8266)

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x80u /* 128u */
#endif



#elif defined(OTHER_ARCH_DEBUG)

#include <stdio.h>
#include <time.h>

#define CURRENTTIME() CurrentTime()

#define DISABLE_INTERRUPTS()

#define ENABLE_INTERRUPTS()

#define TIME_T_TYPE uint32_t


#define CONFIG_ENABLE_SYSTEM_ASSERT
#define CONFIG_SYSTEM_ASSERT_BEHAVIOR(file_, line_) printf("assert: %s:%d\n", file_, line_)

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x20u /* 32u */
#endif



#define MEMDUMP_

#define MEMDUMP_ROW_WIDTH CONFIG_MEMORY_REGION_BLOCK_SIZE


#elif defined(ARDUINO_TEENSY_MICROMOD) || defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY36) || defined(ARDUINO_TEENSY35) || defined(ARDUINO_TEENSY31) || defined(ARDUINO_TEENSY32) || defined(ARDUINO_TEENSY30) || defined(ARDUINO_TEENSYLC)

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x200u /* 512u */
#endif



#elif defined(ESP32)

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x200u /* 512u */
#endif



#else

#pragma message("WARNING: This embedded platform and/or tool-chain may not be supported. Trying to build using the Arduino platform and/or tool-chain.")

#include <Arduino.h>

#define CURRENTTIME() micros()

#define DISABLE_INTERRUPTS() noInterrupts()

#define ENABLE_INTERRUPTS() interrupts()

#define TIME_T_TYPE uint32_t

#if !defined(CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS)
#define CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS 0x20u /* 32u */
#endif



#endif




/* Define "true" if not defined. */
#if !defined(true)
#define true 0x1u
#endif




/* Define "false" if not defined. */
#if !defined(false)
#define false 0x0u
#endif




/* Define "NULL" if not defined. */
#if !defined(NULL)
#if !defined(__cplusplus)
#define NULL ((void *)0x0)
#else
#define NULL 0x0
#endif
#endif




/* Define "zero" if not defined. */
#if !defined(zero)
#define zero 0x0u
#endif




/* Define a general return failure for
return values. */
#if !defined(RETURN_FAILURE)
#define RETURN_FAILURE 0x0u
#endif




/* Define a general return success
for return values. */
#if !defined(RETURN_SUCCESS)
#define RETURN_SUCCESS 0x1u
#endif




/* Define the raw size of the heap in bytes based on the number of blocks
the heap contains and the size of each block in bytes. */
#if !defined(ALL_MEMORY_REGIONS_SIZE_IN_BYTES)
#define ALL_MEMORY_REGIONS_SIZE_IN_BYTES CONFIG_ALL_MEMORY_REGIONS_SIZE_IN_BLOCKS * CONFIG_MEMORY_REGION_BLOCK_SIZE
#endif





/* Define the size in bytes of the OS product name which is accessible through
xSystemGetSystemInfo(). */
#if !defined(OS_PRODUCT_NAME_SIZE)
#define OS_PRODUCT_NAME_SIZE 0x6u
#endif




/* Define the OS product name which is accessible through xSystemGetSystemInfo(). */
#if !defined(OS_PRODUCT_NAME)
#define OS_PRODUCT_NAME "HeliOS"
#endif




/* Define the OS product major version number which is accessible through
xSystemGetSystemInfo(). */
#if !defined(OS_MAJOR_VERSION_NO)
#define OS_MAJOR_VERSION_NO 0x0u
#endif




/* Define the OS product minor version number which is accessible through
xSystemGetSystemInfo(). */
#if !defined(OS_MINOR_VERSION_NO)
#define OS_MINOR_VERSION_NO 0x3u
#endif




/* Define the OS product patch version number which is accessible through
xSystemGetSystemInfo(). */
#if !defined(OS_PATCH_VERSION_NO)
#define OS_PATCH_VERSION_NO 0x3u
#endif




/* Define the macro which sets the privileged flag to true when
the next call to xMemAlloc() and xMemFree() is for protected
memory. */
#if !defined(ENTER_PRIVILEGED)
#define ENTER_PRIVILEGED() sysFlags.privileged = true
#endif




/* Define the macro which sets the privileged flag to false to
exit protected memory mode.

NOTE: This should only be called from within xMemAlloc() and
xMemFree() since both system calls will automatically exit
privileged mode before they return. */
#if !defined(EXIT_PRIVILEGED)
#define EXIT_PRIVILEGED() sysFlags.privileged = false
#endif




/* Define a macro to access the privileged system flag which is
used by xMemAlloc() and xMemFree() to determine when to set an
entry in the heap to protected. */
#if !defined(SYSFLAG_PRIVILEGED)
#define SYSFLAG_PRIVILEGED() sysFlags.privileged
#endif




/* Define a macro to access the running system flag which is used
by xTaskStartScheduler() to indicate whether the scheduler is
running. */
#if !defined(SYSFLAG_RUNNING)
#define SYSFLAG_RUNNING() sysFlags.running
#endif




/* Define a macro to access the overflow system flag which is used
by the scheduler to determine when a task's runtime has overflowed
and all runtimes need to be reset. */
#if !defined(SYSFLAG_OVERFLOW)
#define SYSFLAG_OVERFLOW() sysFlags.overflow
#endif




/* Define a macro to access the corrupt system flag which is used
by the memory management system calls to flag if corruption
of the heap has been detected. */
#if !defined(SYSFLAG_CORRUPT)
#define SYSFLAG_CORRUPT() sysFlags.corrupt
#endif



/* Define a marco which makes null pointer checks more readable and
concise */
#if !defined(ISNOTNULLPTR)
#define ISNOTNULLPTR(p) ((NULL) != ( p ))
#endif




/* Define a marco which makes null pointer checks more readable and
concise */
#if !defined(ISNULLPTR)
#define ISNULLPTR(p) ((NULL) == ( p ))
#endif




/* Define a macro to assert if assertions are enabled through
the CONFIG_ENABLE_SYSTEM_ASSERT setting. */
#if !defined(SYSASSERT)
#if !defined(CONFIG_ENABLE_SYSTEM_ASSERT)
#define SYSASSERT(x)
#else
#define SYSASSERT(x) if (false == (x)) SystemAssert(__FILE__, __LINE__)
#endif
#endif


#if !defined(MEMORY_CHECK_REGION_OPTION_WO_ADDR)
#define MEMORY_CHECK_REGION_OPTION_WO_ADDR 0x1u
#endif


#if !defined(MEMORY_CHECK_REGION_OPTION_W_ADDR)
#define MEMORY_CHECK_REGION_OPTION_W_ADDR 0x2u
#endif


#define BITCHECK(x, n) (( x ) & (1 << ( n )))
#define BITSET(x, n) (( x ) |= (1 << ( n )))
#define BITUNSET(x, n) (( x ) &= ~(1 << ( n )))



/* Define a macro to convert a heap memory address to it's corresponding
heap entry. */
#if !defined(ADDR2ENTRY)
#define ADDR2ENTRY(a, r) (MemoryEntry_t *)((Byte_t *)( a ) - (( r )->entrySizeInBlocks * CONFIG_MEMORY_REGION_BLOCK_SIZE))
#endif



/* Define a macro to convert a heap entry to it's corresponding heap memory
address. */
#if !defined(ENTRY2ADDR)
#define ENTRY2ADDR(a, r) (void *)((Byte_t *)( a ) + (( r )->entrySizeInBlocks * CONFIG_MEMORY_REGION_BLOCK_SIZE))
#endif

#endif