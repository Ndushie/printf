#include "main.h"

/**
 * handle_write_char - Prints a character
 *
 * @c: character to be printed
 * @buffer: Buffer array to handle printing.
 * @flags: active flags for formatting
 * @width: width specifier
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chararacters to be printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
			write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string to the buffer
 *
 * @is_negative: Variable list of arguments
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array to store the characters
 * @flags: Flag specifiers for formatting
 * @width: width specifier for formatting
 * @precision: precision specifier for formatting
 * @size: Size specifier for formatting
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char padding = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		len, padding, extra_ch));
}

/**
 * write_num - Write a number to a bufffer
 *
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array to store the characters
 * @flags: Flag specifiers for formatting
 * @width: width specifier for formatting
 * @precis: Precision specifier for formatting
 * @len: Number length.
 * @padding: Padding character
 * @extra_c: Extra character
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int precis,
	int len, char padding, char extra_c)
{
	int a, padd_start = 1;

	if (precis == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (precis == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padding = ' ';
	if (precis > 0 && precision < len)
		padding = ' ';
	while (precis > len)
		buffer[--ind] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (a = 1; a < width - len + 1; a++)
			buffer[a] = padding;
		buffer[a] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], len - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], len));
}

/**
 * write_unsgnd - Writes an unsigned number to the buffer
 *
 * @is_negative: Flag indicating if the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: buffer array to store the characters
 * @flags: Flags specifiers for formatting
 * @width: Width specifier for formatting
 * @precision: Precision specifier for formatting
 * @size: Size specifier for formatting
 *
 * Return: Number of written characters to the buffer.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1, a = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precis == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precis > 0 && precis < len)
		padding = ' ';
	while (precis > len)
	{
		buffer[--ind] = '0';
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (width > len)
	{
		for (a = 0; a < width - len; a++)
			buffer[a] = padding;

		buffer[a] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], a));
		}
		else
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], len));
		}
	}
	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - Write a memory address to the buffer
 *
 * @buffer: buffer array to store the characters
 * @ind: Index at which the number starts in the buffer
 * @len: Length of the memory address
 * @width: Width specifier for formatting
 * @flags: Flags specifier for foematting
 * @padding: padding character to be used
 * @extra_c: extra character to be included
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int len,
	int width, int flags, char padding, char extra_c, int padd_start)
{
	int a;

	if (width > len)
	{
		for (a = 3; a < width - len + 3; a++)
			buffer[a] = padding;
		buffer[a] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], len - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
