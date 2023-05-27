#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * reverse - reverses a string in place
 * @s: string to reverse
 */
static void reverse(char *s)
{
	int a, b;
	char c;

	for (a = 0, b = strlen(s) - 1; a < b; a++, b--)
	{
		c = s[a];
		s[a] = s[b];
		s[b] = c;
	}
}

/**
 * _itoa - converts an integer to a string
 * @n: integer to convert
 *
 * Return: pointer to the resulting string
 */
static char *_itoa(int n)
{
	char *s;
	int a, sign, rem;

	s = malloc(sizeof(char) * 12);
	if (!s)
		return (NULL);
	sign = n;
	a = 0;

	do {
		rem = n % 10;
		s[a++] = (rem > 0) ? rem + '0' : -rem + '0';
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[a++] = '-';
	s[a] = '\0';
	reverse(s);
	return (s);
}

/**
 * _printf - produces output according to a format
 * @format: character string
 *
 * Return: the number of characters printed
 */
int my_printf(const char *format, ...)
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
			else if (*format == 'd' || *format == 'i')
			{
				s = _itoa(va_arg(args, int));
				count += write(1, s, strlen(s));
				free(s);
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
