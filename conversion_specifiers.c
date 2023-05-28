#include "main.h"
/**
 * print_char - Prints a single character
 *
 * @types: Variable argument list
 *
 * @buffer: Buffer array for handling the print
 *
 * @flags:  Formatting flags
 *
 * @width: Width specification
 *
 * @precision: Precision specification
 *
 * @size: Size specifier
 *
 * Return: Number of chararacters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
 * print_string - Prints a string
 *
 * @types: Variable argument list
 * @buffer: Buffer array for handling the print
 * @flags: Formatting flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, a;
	char *string = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = "      ";
	}

	while (string[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &string[0], length);
			return (width);
		}
	}

	return (write(1, string, length));
}
/**
 * print_percent - Prints a percent sign
 *
 * @types: Variable argument list
 *
 * @buffer: Buffer array for handling print
 *
 * @flags:  Formatting flags
 *
 * @width: Width specifier
 *
 * @precision: Precision specification
 *
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/**
 * print_int - Prints an integer
 * @types: List of arguments
 * @buffer: Array to store the printed characters
 * @flags: Active flags for formatting
 * @width: Specified width for printing
 * @precision: Specified precision for printing
 * @size: Specified size for printing
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int b = va_arg(types, long int);
	unsigned long int number;

	b = convert_size_number(b, size);

	if (b == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)b;

	if (b < 0)
	{
		number = (unsigned long int)((-1) * b);
		is_negative = 1;
	}

	while (number > 0)
	{
		buffer[a--] = (number % 10) + '0';
		number /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number in binary format
 * @types: List of arguments
 * @buffer: Array to store the printed characters
 * @flags: Active flags for formatting
 * @width: Specified width for printing
 * @precision: Specified precision for printing
 * @size: Specified size for printing
 * Return: Number of characters printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, z, sum;
	unsigned int a[32];
	int count;
	char i;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	a[0] = x / y;
	for (z = 1; z < 32; z++)
	{
		y /= 2;
		a[z] = (x / y) % 2;
	}
	for (z = 0, sum = 0, count = 0; z < 32; z++)
	{
		sum += a[z];
		if (sum || z == 31)
		{
			i = '0' + a[z];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
