#include "main.h"r
/**
 * print_unsigned - Prints an unsigned number

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

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
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

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
