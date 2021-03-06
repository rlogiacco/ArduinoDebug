/*
 FormattingSerialDebug.h - MicroDebug library
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

#ifndef SERIAL_DEBUG_H_
#define SERIAL_DEBUG_H_

    #if (defined ARDUINO && (!defined(SERIAL_DEBUG) || SERIAL_DEBUG))
		#pragma message("MicroDebug ENABLED")
        #include <Arduino.h>
        #include <stdio.h>

/*
 * d, i	int as a signed decimal number.
 * u	decimal unsigned int.
 * l	long as a signed decimal number.
 * lu	decimal unsigned long.
 * f, F	double in normal (fixed-point) notation. 'f' and 'F' only differs in how the strings for an infinite number or NaN are printed ('inf', 'infinity' and 'nan' for 'f', 'INF', 'INFINITY' and 'NAN' for 'F').
 * e, E	double value in standard form ([-]d.ddd e[+/-]ddd). An E conversion uses the letter E (rather than e) to introduce the exponent. The exponent always contains at least two digits; if the value is zero, the exponent is 00. In Windows, the exponent contains three digits by default, e.g. 1.5e002, but this can be altered by Microsoft-specific _set_output_format function.
 * g, G	double in either normal or exponential notation, whichever is more appropriate for its magnitude. 'g' uses lower-case letters, 'G' uses upper-case letters. This type differs slightly from fixed-point notation in that insignificant zeroes to the right of the decimal point are not included. Also, the decimal point is not included on whole numbers.
 * x, X	unsigned int as a hexadecimal number. 'x' uses lower-case letters and 'X' uses upper-case. Prefix with 'l' to print long numbers.
 * o	unsigned int in octal. Prefix with 'l' to print long numbers.
 * s	null-terminated string.
 * c	char (character).
 * p	void * (pointer to void) in an implementation-defined format.
 * a, A	double in hexadecimal notation, starting with "0x" or "0X". 'a' uses lower-case letters, 'A' uses upper-case letters.
 * n	Print nothing, but write number of characters successfully written so far into an integer pointer parameter.
 * %	a literal '%' character (this type doesn't accept any flags, width, precision or length).
 */

        #ifndef SERIAL_DEBUG_IMPL
            #define SERIAL_DEBUG_IMPL Serial
        #endif

        #ifdef ARDUINO_ARCH_AVR
		int _serialDebug(char c, FILE * file);
        #define SERIAL_DEBUG_SETUP(speed) SERIAL_DEBUG_IMPL.begin(speed);fdevopen( &_serialDebug, 0 )
		#define DEBUG(format, ...) printf(format, ##__VA_ARGS__); SERIAL_DEBUG_IMPL.println()
		#ifdef F
        void printf(const __FlashStringHelper *format, ...);
        #endif
        #endif

        #if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_STM32F4)
        #pragma message("MicroDebug DISABLED: FormattingSerial not implemented on your architecture")
		#define SERIAL_DEBUG_SETUP(speed) SERIAL_DEBUG_IMPL.begin(speed)
        #define DEBUG(format, ...) printf(format, ##__VA_ARGS__); fflush(stdout); SERIAL_DEBUG_IMPL.println()
		#endif

    #else
		#pragma message("MicroDebug DISABLED")
        #define DEBUG(format, ...)
        #define SERIAL_DEBUG_SETUP(speed)
    #endif // SERIAL_DEBUG
#endif // SERIAL_DEBUG_H_
