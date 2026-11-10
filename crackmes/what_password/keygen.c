#include <stdio.h>
#define XOR_KEY 0x27
int main(){
	// I used pw + DAT_00404029 as
	// array
	char pw[] = {
	0x4e,0x49,0x1d,0x42,0x7c,
	0x41,0x7c,0x33,0x75,0x6a,
	0x6b,0x3c,0x7e,0x7f,0xcb,
	0x00}; // null character
		
	char val1 = 0x0;
	char val2 = 0x0;
	char val3 = 0x02;
	printf("KEY: ");
	for(char *p = pw; *p != 0x00 ;p++){
		val1 = *p ^ XOR_KEY;
		val1 += val3;
		printf("%c",val1);

		//;update the variables
		val3 += 0x02;
		val2 += 0x01;
	}

	printf("\n");
	return 0;
}
