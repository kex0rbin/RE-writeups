#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){
		int a = 5;
		srand(time(NULL));
			// hex values
			unsigned char check1[] = {
			0x30,0x31,0x32,0x33,0x34,0x35,0x36,
			0x37,0x38,0x39
			};
			unsigned char check2[] = {
			0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,
			0x2B,0x2C,0x2D,0x2E,0x2F,0x3a,0x3b,0x3c,0x3d,0x3e,
			0x3f,0x40,0x5b,0x5d,0x5e,0x7b,0x7d,0x7e
			};
			char check3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			char check4[] = "abcdefghijklmnopqrstuvwxyz";
			int randm = 0;
		while(a > 0){
			printf("VALID KEY: { ");
			for(int i=0; i<13; i++){
				if(i < 9){
					if(i < 3){
					randm = rand() % sizeof(check1);
					printf("%c",check1[randm]);
					}
					if(i >=3 && i < 6){
					randm = rand() % sizeof(check2);
					printf("%c",check2[randm]);
					}
					if(i >= 6){
					randm = rand() % strlen(check3);
					printf("%c", check3[randm]);
					}
				}else{
					randm = rand() % strlen(check4); 	
					printf("%c", check4[randm]);
				}
			}
			printf(" }\n");
			a--;
		}
}

