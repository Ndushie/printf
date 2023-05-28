#include "main.h"
/**
 * print_pointer - Prints the value of a pointer variable
 *
 * @types: Variable list of arguments
 * @buffer: Buffer array to handle printing
 * @flags: flags to be formatted
 * @width: width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padding = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)addrs;

	while (num_address > 0)
	{
		buffer[ind--] = map_to[num_address % 16];
		num_address /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;
	return (write_pointer(buffer, ind, length,
		width, flags, padding, extra_c, padd_start));
}
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 *
 * @types: Variable list of arguments
 * @buffer: Buffer array to handle print
 * @flags: flags to be formatted
 * @width: width specifier
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[a] != '\0')
	{
		if (is_printable(str[a]))
			buffer[a + offset] = str[a];
		else
			offset += append_hexa_code(str[a], buffer, a + offset);

		a++;
	}

	buffer[a + offset] = '\0';

	return (write(1, buffer, a + offset));
}
/**
 * print_reverse - Prints reverse string.
 *
 * @types: Variable list of arguments
 * @buffer: Buffer array to handle print
 * @flags: flags to be formatted
 * @width: width specification
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Numbers of chars printed
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int a, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (a = 0; str[a]; a++)
	for (a = a - 1; a >= 0; a--)
	{
		char z = str[a];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**
 * print_rot13string - Prints a string in rot13 encoding
 * @types: List of arguments
 * @buffer: Array to store the printed characters
 * @flags: Active flags for formatting
 * @width: Specified width for printing
 * @precision: Specified precision for printing
 * @size: Specified size for printing
 * Return: Number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int a, b;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				x = out[b];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[b])
		{
			x = str[a];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
