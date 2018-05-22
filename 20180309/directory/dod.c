#include <stdio.h>
#include <unistd.h>

int main(){
	char *p;

	p=getcwd(NULL,0);
	puts(p);
	return 0;
}
