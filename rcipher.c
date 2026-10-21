#include <stdio.h>

void
main(void)
{
	int a[3] = {66,67,68};
	int i = 0;
	while (i < 3)
	{
		printf("%c", (char)a[i++]);
	}
	return;
}
