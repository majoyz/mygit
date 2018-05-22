#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void printdir(char *path,char *name){
	DIR *dir=opendir(path);
	if(dir==NULL){
		perror("opendir");
		return;
	}
	struct dirent *p;
	char dirname[512]={0};
	char *fpath;
	while((p=readdir(dir))!=NULL){
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
		}else{
			if(0==strcmp(p->d_name,name)){
				char *root=getcwd(NULL,0);
				chdir(path);
				fpath=getcwd(NULL,0);
				printf("%s/%s\n",fpath,name);
				chdir(root);
			}
			else if(4==p->d_type){
				sprintf(dirname,"%s%s%s",path,"/",p->d_name);
				printdir(dirname,name);
			}
		}
	}
	closedir(dir);
}

int main(int argc,char *argv[]){
	if(argc!=3){
		printf("argc error\n");
		return -1;
	}
	printdir(argv[1],argv[2]);
	return 0;
}
