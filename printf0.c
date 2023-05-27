#include <stdarg.h>
#include <unistd.h>
#include "main.h"
#include <string.h>

/**
 * _printf - produces output according to a format
 * @format: character string
 *
 * Return: the number of characters printed (excluding the null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char c;
	char *s;
	
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			c = (char)va_arg(args, int);
			count += (*format == 'c') ? write(1, &c, 1) : 0;
			if (*format == 's')
			{
				s = va_arg(args, char *);
				count += write(1, s, strlen(s));
			}
			count += (*format == '%') ? write(1, "%", 1) : 0;
		}
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
