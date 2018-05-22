#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void printdir(char *path,int width){
	DIR *dir=opendir(path);
	if(dir==NULL){
		perror("opendir");
		return;
	}
	struct dirent *p;
	char dirname[128]={0};
	while((p=readdir(dir))!=NULL){
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
		}else{
			printf("%*s%s\n",width," ",p->d_name);
			if(4==p->d_type){
				//路径拼接
				sprintf(dirname,"%s%s%s",path,"/",p->d_name);
				printdir(dirname,width+4);
			}
		}
	}
	closedir(dir);
}

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("argc error\n");
		return -1;
	}
	puts(argv[1]);
	printdir(argv[1],0);
	return 0;
}
