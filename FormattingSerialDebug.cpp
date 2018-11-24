/*
 FormattingSerialDebug.cpp - MicroDebug library
 Copyright (c) 2014 Roberto Lo Giacco.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as 
 published by the Free Software Foundation, either version 3 of the 
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <FormattingSerialDebug.h>

#if (!defined(SERIAL_DEBUG) || SERIAL_DEBUG)
#if defined(ARDUINO_ARCH_AVR)
int _serialDebug(char c, __attribute__ ((unused)) FILE * file) {
	SERIAL_DEBUG_IMPL.write(c);
	return c;
}
#endif

#if defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_STM32F4)
// Still looking for a valid implementation
#endif


#ifdef F
#include <stdarg.h>
void printf(const __FlashStringHelper *format, ...) {
	char buffer[256];
	va_list args;
	va_start(args, format);
	#if defined(ARDUINO_ARCH_STM32F4) || defined(ARDUINO_ARCH_STM32F3) || defined(ARDUINO_ARCH_STM32F2) || defined(ARDUINO_ARCH_STM32F1)
	vsnprintf(buffer, sizeof(buffer), (const char *)format, args);
	#else
	vsnprintf_P(buffer, sizeof(buffer), (const char *)format, args); // progmem for AVR
	#endif
	va_end(args);
	SERIAL_DEBUG_IMPL.print(buffer);
}
#endif
#endif
