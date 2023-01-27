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

/**
 * print_address - prints address of a given pointer or variable
 * @list: list of arguments
 * Return: count of printed characters
 */

int print_address(va_list list)
{
	long int p;
	int len;

	len = 0;
	_write_char('0');
	_write_char('x');
	p = va_arg(list, long int);
	len += 2;
	len += print_hex3(p);
	return (len);
}

/**
 * print_hex3 - prints hexadecimal in small letters
 * @num: number to find hex
 * Return: count of chars printed
 */

int print_hex3(long int num)
{
	int len;
	int rem_num;
	char *hex_rep;
	char *rev_hex;

	if (num < 1)
		return (-1);
	len = base_len(num, 16);
	hex_rep = malloc(sizeof(char) * len + 1);
	if (hex_rep == NULL)
		return (-1);
	for (len = 0; num > 0; len++)
	{
		rem_num = num % 16;
		if (rem_num > 9)
		{
			rem_num = hex_check(rem_num, 'x');
			hex_rep[len] = rem_num;
		}
		else
			hex_rep[len] = rem_num + 48;
		num = num / 16;
	}
	hex_rep[len] = '\0';
	rev_hex = rev_string(hex_rep);
	if (rev_hex == NULL)
		return (-1);
	write_base(rev_hex);
	free(hex_rep);
	free(rev_hex);
	return (len);
}
