#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

/**
* struct convert - defines a structure for symbols and functions
*
* @sym: The operator
* @f: The function associated
*/
struct convert
{
	char *sym;
	int (*f)(va_list);
};
typedef struct convert conver_t;

struct p_f
{
	int (*func)(char *);
};
typedef struct p_f p_func;
/*Main functions*/
int parser(const char *format, conver_t f_list[], va_list arg_list);
int _printf(const char *format, ...);
int _write_char(char);
int print_char(va_list);
int print_string(va_list);
int print_percent(va_list);
int print_integer(va_list);
int print_number(va_list);
int print_binary(va_list);
int print_reversed(va_list arg);
int rot13(va_list);
int unsigned_integer(va_list);
int print_octal(va_list list);
int print_hex(va_list list);
int print_heX(va_list list);

/*Helper functions*/
unsigned int base_len(unsigned int, int);
char *rev_string(char *);
void write_base(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
int print_unsgined_number(unsigned int);

/**
 * _printf - Receives the main string and all the necessary parameters to
 * print a formated string
 * @format: A string containing all the desired characters
 * Return: A total count of the characters printed
 */
int _printf(const char *format, ...)
{
	int printed_chars;
	conver_t f_list[] = {
		{"s", print_string},
		{"o", print_octal},
		{NULL, NULL}
	};
	va_list arg_list;

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);
	/*Calling parser function*/
	printed_chars = parser(format, f_list, arg_list);
	va_end(arg_list);
	return (printed_chars);
}

/**
 * _memcpy - copy memory area
 * @dest: Destination for copying
 * @src: Source to copy from
 * @n: The number of bytes to copy
 * Return: The _memcpy() function returns a pointer to dest.
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * hex_check - Checks which hex function is calling it
 * @num: Number to convert into letter
 * @x: Tells which hex function is calling it
 * Return: Ascii value for a letter
 */
int hex_check(int num, char x)
{
	char *hex = "abcdef";
	char *Hex = "ABCDEF";

	num = num - 10;
	if (x == 'x')
		return (hex[num]);
	else
		return (Hex[num]);
	return (0);
}


/**
 * base_len - Calculates the length for an octal number
 * @num: The number for which the length is being calculated
 * @base: Base to be calculated by
 * Return: An integer representing the length of a number
 */
unsigned int base_len(unsigned int num, int base)
{
	unsigned int i;

	for (i = 0; num > 0; i++)
	{
		num = num / base;
	}
	return (i);
}
/**
 * rev_string - reverses a string in place
 *
 * @s: string to reverse
 * Return: A pointer to a character
 */
char *rev_string(char *s)
{
	int len;
	int head;
	char tmp;
	char *dest;

	for (len = 0; s[len] != '\0'; len++)
	{}

	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);

	_memcpy(dest, s, len);
	for (head = 0; head < len; head++, len--)
	{
		tmp = dest[len - 1];
		dest[len - 1] = dest[head];
		dest[head] = tmp;
	}
	return (dest);
}

/**
 * write_base - sends characters to be written on standard output
 * @str: String to parse
 */
void write_base(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_write_char(str[i]);
}

/**
 * print_octal - Prints the numeric representation of a number in octal base
 * @list: List of all the arguments passed to the program
 * Return: Number of symbols printed to stdout
 */
int print_octal(va_list list)
{
	unsigned int num;
	int len;
	char *octal_rep;
	char *rev_str;

	num = va_arg(list, unsigned int);

	if (num == 0)
		return (_write_char('0'));
	if (num < 1)
		return (-1);
	len = base_len(num, 8);

	octal_rep = malloc(sizeof(char) * len + 1);
	if (octal_rep == NULL)
		return (-1);
	for (len = 0; num > 0; len++)
	{
		octal_rep[len] = (num % 8) + 48;
		num = num / 8;

	}
	octal_rep[len] = '\0';
	rev_str = rev_string(octal_rep);
	if (rev_str == NULL)
		return (-1);

	write_base(rev_str);
	free(octal_rep);
	free(rev_str);
	return (len);
}
/**
 * _write_char - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_char(char c)
{
	return (write(1, &c, 1));
}

int print_string(va_list list)
{
	int i;
	char *str;

	str = va_arg(list, char *);
	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
		_write_char(str[i]);
	return (i);
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
int main()
{
	_printf("%s%o%s", "julius",  20, "mwass");
	return (0);
}

