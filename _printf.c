#include "main.h"

#include <unistd.h>

static int print_char(char c)
{
	return (int)write(1, &c, 1);
}

static int print_string(const char *str)
{
	int count;

	if (str == NULL)
		str = "(null)";
	count = 0;
	while (*str)
	{
		count += print_char(*str);
		str++;
	}
	return (count);
}

static int print_number(long value)
{
	char buffer[20];
	int index;
	int count;

	count = 0;
	if (value < 0)
	{
		count += print_char('-');
		value = -value;
	}
	if (value == 0)
		return (count + print_char('0'));
	index = 0;
	while (value > 0)
	{
		buffer[index++] = (char)('0' + (value % 10));
		value /= 10;
	}
	while (index-- > 0)
		count += print_char(buffer[index]);
	return (count);
}

/**
 * _printf - produce output according to a format
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error.
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count;
	int printed;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format != '%')
		{
			count += print_char(*format++);
			continue;
		}
		format++;
		if (*format == '\0')
		{
			va_end(args);
			return (-1);
		}
		switch (*format)
		{
		case 'c':
			printed = print_char((char)va_arg(args, int));
			break;
		case 's':
			printed = print_string(va_arg(args, const char *));
			break;
		case '%':
			printed = print_char('%');
			break;
		case 'd':
		case 'i':
			printed = print_number((long)va_arg(args, int));
			break;
		default:
			printed = print_char('%');
			printed += print_char(*format);
			break;
		}
		count += printed;
		format++;
	}
	va_end(args);
	return (count);
}
