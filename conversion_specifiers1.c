#include "main.h"
/**
 * print_unsigned - Prints an unsigned number
 *
 * @types: Variable argument list
 * @buffer: Buffer array for handling the print
 * @flags: Formatting flags
 * @width: width specifications
 * @precision: Precision specification
 * @size: Size specifier

 * Return: Number of characters printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
/**
 * print_octal - Prints an unsigned number in octal notation
 *
 * @types: Variable argument list
 * @buffer: Buffer array to handle print
 * @flags: Formatting flags
 * @width: width specifications
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_number = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_number != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 *
 * @types: List of arguments
 * @buffer: Array to store the printed characters
 * @flags: Active flags for formatting
 * @width: Specified width for printing
 * @precision: Specified precision for printing
 * @size: Specified size for printing

 * Return: Number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 *
 * @types: List of arguments
 * @buffer: Array to store the printed characters
 * @flags: Active flags for formatting
 * @width: Specified width for printing
 * @precision: Specified precision for printing
 * @size: Specified size for printing
 *
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 *
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Array to store the printed characters
 * @flags: Active flags for formatting
 * @flag_ch: Active flags for formatting
 * @width: Specified width for printing
 * @precision: Specified precision for printing
 * @size: Specified size for printing
 *
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
