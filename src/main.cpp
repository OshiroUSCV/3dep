#include <stdio.h>

#include "vec.h"


int main()
{
	printf("Hello World!\n");

	vec2f v_1(3, 4);
	vec2f v_2(4, -4);
	vec2f v_3 = v_1 - v_2;

	v_1.Print();
	v_2.Print();
	v_3.Print();

	while (true) {}
}