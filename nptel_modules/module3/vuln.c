#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vuln(char *s)
{
    char buffer[64];
    strcpy(buffer, s);
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "Enter a string!\n");
        exit(EXIT_FAILURE);
    }
    vuln(argv[1]);
}
