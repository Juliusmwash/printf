#ifndef PRINT_F
#define PRINT_F

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

/*Main functions*/
int print_heX2(unsigned int);
int parser(const char *format, conver_t f_list[], va_list arg_list);
int printfFlags(int *i, const char *format, conver_t f_list[], va_list arg_list);
int parser_helper(int *i1, const char *format, conver_t f_list[], va_list arg_list);
int _printf(const char *format, ...);
int _write_char(char);
int _putchars(char *s);
int print_char(va_list);
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
int print_address(va_list list);
int print_hex3(long int num);

/*Helper functions*/
int hex_check(int, char);
unsigned int base_len(unsigned int, int);
char *rev_string(char *);
void write_base(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
int print_unsgined_number(unsigned int);


#endif
