#include "func.h"

int main(){
	typedef struct student{
		int num;
		char name[20];
		float score;
	}stu,*pstu;
	stu a[3]={{1001,"rongai",98},{1002,"meimei",99},{1003,"guangtou",80.5}};
	int fd=open("stuinfo.txt",O_CREAT|O_TRUNC|O_RDWR,0775);
	if(-1==fd){
		perror("open");
		return 0;
	}
	int i;
	for(i=0;i<3;i++){
		write(fd,&a[i],sizeof(stu));
	}
	lseek(fd,0,SEEK_SET);
	memset(a,0,sizeof(a));
	int ret;
	i=0;
	while((ret=read(fd,&a[i],sizeof(stu)))>0){
		if(ret==-1){
			perror("read");
			return 0;
		}
		printf("%4d %12s %6.2f\n",a[i].num,a[i].name,a[i].score);
		i++;
	}
	close(fd);
	return 0;
}
