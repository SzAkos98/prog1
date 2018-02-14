#include <stdio.h>

int main ()
{
	int h=0;
	int n=0x01;
	while (n != 0)
		{
		n<<=1;
		h++;
		}
	printf("A szohossz ezen a gepen: %d\n", h);
	return 0;
}
