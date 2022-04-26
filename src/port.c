/**
 * @file port.c
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel sources for portability layer
 * @version 0.3.3
 * @date 2022-03-24
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

#include "port.h"


#if defined(ARDUINO_ARCH_AVR)

Ticks_t _SysGetSysTicks_(void) {

  return timer0_overflow_count;

}

void _SysInit_(void) {

	return;

}

#elif defined(ARDUINO_ARCH_SAM)

Ticks_t _SysGetSysTicks_(void) {

  return GetTickCount();

}

void _SysInit_(void) {

	return;

}

#elif defined(ARDUINO_ARCH_SAMD)

Ticks_t _SysGetSysTicks_(void) {

  return millis();

}

void _SysInit_(void) {

	return;

}

#elif defined(ARDUINO_ARCH_ESP8266)

Ticks_t _SysGetSysTicks_(void) {

  return (Ticks_t)(micros() / 1000ULL);

}

void _SysInit_(void) {

	return;

}

#elif defined(ARDUINO_TEENSY_MICROMOD) || defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY36) || defined(ARDUINO_TEENSY35) || defined(ARDUINO_TEENSY31) || defined(ARDUINO_TEENSY32) || defined(ARDUINO_TEENSY30) || defined(ARDUINO_TEENSYLC)

Ticks_t _SysGetSysTicks_(void) {

  return systick_millis_count;

}

void _SysInit_(void) {

	return;

}

#elif defined(ESP32)

/* Not supported. */

#elif defined(CMSIS_ARCH_CORTEXM)

static volatile Ticks_t sysTicks = zero;

void SysTick_Handler(void) {

	DISABLE_INTERRUPTS();

	sysTicks++;

	ENABLE_INTERRUPTS();

	return;
}

Ticks_t _SysGetSysTicks_(void) {

	return sysTicks;

}

void _SysInit_(void) {

	SysTick_Config(SYSTEM_CORE_CLOCK_FREQUENCY / SYSTEM_CORE_CLOCK_PRESCALER);

	return;

}

#elif defined(DEBUG_ON)

Ticks_t _SysGetSysTicks_(void) {

	struct timespec t;

	clock_gettime(CLOCK_MONOTONIC_RAW, &t);

	return (t.tv_sec * 1000000) + (t.tv_nsec / 1000);

}

void _SysInit_(void) {

	return;

}

#endif

