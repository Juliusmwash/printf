#include "main.h"

/**
 * printfFlags - executes according to a flag if any
 * @i: iteration variable
 * @format: string being formated
 * @f_list: list of all possible functions
 * @arg_list: list of arguments passed to the program
 * Return: count of the characters printed
 */
int printfFlags(int *i, const char *format, conver_t f_list[], va_list arg_list)
{
	int j, count;

	count = 0;
	j = *(i);
	if(format[j] == '%' && format[j + 1] == '#')
	{
		if (format[j + 2] == 'x' && format[j + 3] == 'd')
		{
			_write_char('0');
			_write_char('x');
			count += 2;
			count += f_list[10].f(arg_list);
		}
		else if (format[j + 2] == 'X' && format[j + 3] == 'd')
		{
			_write_char('0');
			_write_char('X');
			count += 2;
			count += f_list[11].f(arg_list);
		}
		else if (format[j + 2] == 'o' && format[j + 3] == 'd')
		{
			_write_char('0');
			count += 1;
			count += f_list[9].f(arg_list);
		}
		(*(i)) += 3;
	}
	return (count);
}


/**
 * parser - Receives the main string and all the necessary parameters to
 * print a formated string.
 * @format: A string containing all the desired characters.
 * @f_list: A list of all the posible functions.
 * @arg_list: A list containing all the argumentents passed to the program.
 * Return: A total count of the characters printed.
 */
int parser(const char *format, conver_t f_list[], va_list arg_list)
{
	int i, j, r_val, printed_chars;

	printed_chars = 0;
	for (i = 0; format[i] != '\0'; i++)/* Iterates through the main str*/
	{
		if (format[i] == '%') /*Checks for format specifiers*/
		{
			/*Iterates through struct to find the right func*/
			for (j = 0; f_list[j].sym != NULL; j++)
			{
				if (format[i + 1] == f_list[j].sym[0])
				{
					r_val = f_list[j].f(arg_list);
					if (r_val == -1)
						return (-1);
					printed_chars += r_val;
					break;
				}
			}
			if (f_list[j].sym == NULL && format[i + 1] != ' ')
			{
				if (format[i + 1] != '\0')
				{
					_write_char(format[i]);
					_write_char(format[i + 1]);
					printed_chars = printed_chars + 2;
				}
				else
					return (-1);
			}
			i = i + 1; /*Updating i to skip format symbols*/
		}
		else
		{
			_write_char(format[i]); /*call the write function*/
			printed_chars++;
		}
	}
	return (printed_chars);
}
