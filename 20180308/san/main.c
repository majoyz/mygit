#include <stdio.h>

int multi(int a,int b){
	return a*b;
}

int main(){
	int a=5;
	int b=7;
	int c;
	c=multi(a,b);
	printf("%d\n",c);
	return 0;
}
