// Online C compiler to run C program online
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int print_heX2(unsigned int);
int _printf(const char *format, ...);
int _write_char(char);
int print_char(va_list);
int print_address(va_list list);
int print_hex3(long int);
int print_string(va_list);
int print_string2(va_list);
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
int print_heX2(unsigned int);

/*Helper functions*/
unsigned int base_len(unsigned int, int);
char *rev_string(char *);
void write_base(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
int print_unsgined_number(unsigned int);

/**
* struct convert - defines a structure for symbols and functions
*
* @sym: The operator
* @f: The function associated
*/
typedef struct convert
{
	char *sym;
	int (*f)(va_list);
} conver_t;

int parser(const char *format, conver_t f_list[],  va_list arg_list);
/**
 * _printf - Receives the main string and all the necessary parameters to
 * print a formated string
 * @format: A string containing all the desired characters
 * Return: A total count of the characters printed
 */
int _printf(const char *format, ...)
{
	int printed_chars;
	struct convert f_list[] = {
		{"S", print_string2},
		{"p", print_address},
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
void write_base(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_write_char(str[i]);
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
int _write_char(char c)
{
	return (write(1, &c, 1));
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

	_write_char('0');
	_write_char('x');
	p = va_arg(list, long int);
	len = print_hex3(p);
	len += 2;
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

int print_heX2(unsigned int num)
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
			rem_num = hex_check(rem_num, 'X');
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
int print_string2(va_list list)
{
	int i;
	int len;
	int c;
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
	return (len);;
}

int printy(char *s, ...)
{
	int i;
    va_list args;
    va_start(args, s);
   i =  print_string2(args);
    va_end(args);
    return (i);
}

/**
 * print_reversed - Calls a function to reverse and print a string
 * @arg: Argument passed to the function
 * Return: The amount of characters printed
 */
int print_reversed(va_list arg)
{
	int len;
	char *str;
	char *ptr;

	str = va_arg(arg, char *);
	if (str == NULL)
		return (-1);
	ptr = rev_string(str);
	if (ptr == NULL)
		return (-1);
	for (len = 0; ptr[len] != '\0'; len++)
		_write_char(ptr[len]);
	free(ptr);
	return (len);
}

/**
 * rot13 - Converts string to rot13
 * @list: string to convert
 * Return: converted string
 */
int rot13(va_list list)
{
	int i;
	int x;
	char *str;
	char s[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char u[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(list, char *);
	if (str == NULL)
		return (-1);
	for (i = 0; str[i] != '\0'; i++)
	{
		for (x = 0; x <= 52; x++)
		{
			if (str[i] == s[x])
			{
				_write_char(u[x]);
				break;
			}
		}
		if (x == 53)
			_write_char(str[i]);
	}
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
					printf("printedchars: %d\n", r_val);
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
			//printf("printed_chars: %d\n", printed_chars);
			_write_char(format[i]); /*call the write function*/
			printed_chars++;
		}
		//printf("printed_chars2: %d\n", printed_chars);
	}
	return (printed_chars);
}/*
int main() {
    // Write C code here
    //printy("julius\n", "juli\nnameø");
    //printy("Could you print some non-prntable characters?\n%S\nThanks!\n", "Sure:\x1F\x7F\n");
    //int len = printy("%S", "ju \n");
    int len = printy("%S", "\x01\x02\x03\x04\x05\x06\x07");
    printf("\n%d\n", len);
    printy("Could you print some non-prntable characters?\n%S\nThanks!\n", "Sure:\x1F\x7F\n");
    return (0);
}

int main(void)
{
	int len, len2;

	len = _printf("Could you print some non-prntable characters?\n");
	len2 = printf("Could you print some non-prntable characters?\n");
	putchar(10);
	fflush(stdout);
	printf("len: %d\n", len);
	printf("len2: %d\n", len2);
	len = _printf("%S\nThanks!\n", "Sure:xx1Fxx7F\n");
	len2 = printf("Sure:\\x1F\\x7F\\x0A\nThanks!\n");
	printf("len: %d\n", len);
	printf("len2: %d\n", len2);
	len = _printf("Could you print some non-prntable characters?\n%S\nThanks!\n", "Sure:\x1F\x7F\n");
	len2 = printf("Could you print some non-prntable characters?\nSure:\\x1F\\x7F\\x0A\nThanks!\n");
	//len2 = _printf("Could you print some non-prntable characters?\nff\nThanks!\n", "Sure:\x1F\x7F\n");
	printf("len: %d\n", len);
	printf("len2: %d\n", len2);
	if (len != len2)
	{
		printf("Lengths differ.\n");
		fflush(stdout);
		return (1);
	}
	return (0);
}*/

int main(void)
{
	int len, len2;
	void *p = (void *)0x7fff5100b608;

	len = _printf("%p\n", p);
	len2 = printf("%p\n", p);
	fflush(stdout);
	if (len != len2)
	{
		printf("Lengths differ.\n");
		fflush(stdout);
		return (1);
	}
	return (0);
}
