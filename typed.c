#include <stdio.h>

typedef struct me
{
	int i;
}me_2;

int main()
{
	me_2 t;
	t.i = 4;
	int y = t.i + 4;
	printf("%d", y);
	return (y);
}
