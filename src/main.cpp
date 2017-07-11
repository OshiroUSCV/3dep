#include <stdio.h>

#include "vec.h"
#include "mat.h"


int main()
{
	printf("Hello World!\n");

	//vec4f v_1(3, 4);
	//v_1 = 3 * v_1;
	//vec4f v_2(4, -4);
	//vec4f v_3 = v_1 - v_2;

	//v_1.Print();
	//v_2.Print();
	//v_3.Print();

	mat44 mat_test
	(
		vec4f(1,2,3,4),
		vec4f(5,6,7,8),
		vec4f(20,30,40,50),
		vec4f(25,50,75,100)
	);
	mat33 mat_result = mat_test.GetMinor(2,1);

	mat_test.Print();
	mat_result.Print();

	while (true) {}
}