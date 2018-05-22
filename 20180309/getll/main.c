#include "func.h"

void one(struct dirent *p)
{
	//char *fname=p->d_name;
	if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
		return;
	}
	struct stat buf;
	int ret;
	ret=stat(p->d_name,&buf);
	if(-1==ret)
	{
		perror("stat");
		return;
	}
	//printf("%ld\n",sizeof(mode_t));
	char *t=ctime(&buf.st_mtime)+4;
	t[12]=0;
	int shl=buf.st_mode;
	//权限转换区
	int i=0,j=9;
	char qx[11];
	qx[10]=0;
	for(i=0;i<3;i++){
		if(1==shl%2)
			qx[j--]='x';
		else
			qx[j--]='-';
		shl/=2;
		if(1==shl%2)
			qx[j--]='w';
		else
 			qx[j--]='-';
		shl/=2;
		if(1==shl%2)
			qx[j--]='r';
		else
			qx[j--]='-';
		shl/=2;
	}
	shl/=8;
	switch(shl){
		case 1:qx[j]='p';break;
		case 2:qx[j]='c';break;
		case 4:qx[j]='d';break;
		case 6:qx[j]='b';break;
		case 8:qx[j]='-';break;
		case 12:qx[j]='l';break;
		case 14:qx[j]='s';break;
		default:qx[j]='?';break;
	}
	//权限转换区
	printf("%s %ld %s %s %5ld %s %s\n",qx,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,t,p->d_name);
	return;
}

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("argc error\n");
		return -1;
	}
	DIR *dir=opendir(argv[1]);
	if(dir==NULL){
		perror("opendir");
		return -1;
	}
	struct dirent *p;
	//char dirname[512]={0};
	//char *fpath;
	while((p=readdir(dir))!=NULL){
		//chdir(argv[1]);
		one(p);
	}
	closedir(dir);
}
