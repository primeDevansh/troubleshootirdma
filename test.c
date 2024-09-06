#include <stdio.h>

void dbg(char *s) {
	printf("%s", s);
	getc(stdin);
	return;
}

int main() {
    int i = 1;

    while(1)
        dbg("ith step performed");

    return 0;
}