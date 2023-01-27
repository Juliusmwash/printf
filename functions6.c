#include "main.h"

/**
 * print_string2 - prints characters to stdout
 * @list: list of arguments
 * Return: count of characters printed
 */

int print_string2(va_list list)
{
	int i, len, c;
	char *str;

	len = 0;
	str = va_arg(list, char *);
	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
	{
		c = str[i];
		if ((c > 0 && c < 32) || c >= 127)
		{
		if (c < 16)
		{
			_write_char('\\');
			_write_char('x');
			_write_char('0');
			len += print_heX2(c);
			len += 3;
		}
		else
		{
			_write_char('\\');
			_write_char('x');
			len += print_heX2(c);
			len += 2;
		}
		}
		else
		{
			_write_char(str[i]);
			len++;
		}
	}
	return (len);
}
