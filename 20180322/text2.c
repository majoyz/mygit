#include "func.h"

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("error argc\n");
		return -1;
	}
	struct in_addr xx;
	int ret=inet_aton(argv[1],&xx);
	if(ret==0){
		printf("error inet_aton\n");
		return -2;
	}
	printf("xx=%x\n",xx.s_addr);
	return 0;
}
