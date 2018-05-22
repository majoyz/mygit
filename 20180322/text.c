#include "func.h"

int main(){
	short port=1234;
	short nport;
	nport=htons(port);
	printf("port=%x,nport=%x\n",port,nport);
	return 0;
}
