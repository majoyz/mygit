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
		char buf[128]={0};
		sprintf(buf,"%4d %10s %6.2f\n",a[i].num,a[i].name,a[i].score);
		write(fd,buf,strlen(buf));
	}
	lseek(fd,0,SEEK_SET);
	memset(a,0,sizeof(a));
	char out[512]={0};
	int ret;
	while((ret=read(fd,out,sizeof(out)))>0){
		if(ret==-1){
			perror("read");
			return 0;
		}
		printf("%s",out);
	}
	close(fd);
	return 0;
}
