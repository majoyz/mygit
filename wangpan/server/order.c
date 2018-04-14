#include "order.h"

int s_cd(int new_fd,int *procode,char *listname,char *work_dir,char *username){
	int ret;
	size_t i;
	printf("procode=%d,listname=%s,work_dir=%s\n",*procode,listname,work_dir);
	if(strcmp(listname,".")==0){
		ret=1;
	}else if(strcmp(listname,"..")==0){
		if(strcmp(work_dir,"~")==0){
			ret=-1;
		}else{
			get_procode(procode);//改procode值
			i=strlen(work_dir)-1;
			while(work_dir[i]!='/'){//当前工作目录前移
				i--;
			}
			work_dir[i]=0;
			ret=1;
		}
	}else if(strcmp(listname,"/")==0){
		*procode=0;
		strcpy(work_dir,"/");
		ret=1;
	}else{
		ret=listnamesame(procode,listname,username);//改pro
		if(ret==1){
			sprintf(work_dir,"%s%s%s",work_dir,"/",listname);
		}
	}
	i=strlen(work_dir);
	printf("ok?ok=%d\n,procode=%d\n",ret,*procode);
	send(new_fd,&ret,sizeof(int),0);
	if(ret==-1){
		return -1;
	}else{
		send_n(new_fd,&i,sizeof(size_t));
		send_n(new_fd,work_dir,i);
		printf("已发送%ld %s\n",i,work_dir);
		return 0;
	}
}


int s_gets(int new_fd,char *mdfilename){
	struct stat sbuf;
	off_t lenth;
	off_t tmplenth;
	off_t gps=0;
	int tmpopt;
	char path[64]={0};
	sprintf(path,"%s%s","./acloud/",mdfilename);
	puts(path);
	int mdfd=open(path,O_RDONLY);
		recv_n(new_fd,&tmpopt,sizeof(int));//接收选项
		printf("I got option %d\n",tmpopt);
		stat(path,&sbuf);
		lenth=sbuf.st_size;
		if(tmpopt==2){
			recv_n(new_fd,&tmplenth,sizeof(off_t));//已有
			send_n(new_fd,&mdfilename,33);//发过去md5码
			lenth-=tmplenth;
			gps=tmplenth;
		}
		printf("sending mdfilename=%s,size=%ld\n",mdfilename,lenth);
		send_n(new_fd,&lenth,sizeof(off_t));//发送文件大小
		while(1){
			tmplenth=sendfile(new_fd,mdfd,&gps,lenth);
			if(tmplenth<lenth){
				lenth-=tmplenth;
				gps+=tmplenth;
			}else{
				break;
			}
		}
		printf("after sendfile\n");
		close(mdfd);
	return 0;
}

int s_puts(int new_fd,char *filename,char *mdfn,off_t *mysize){//接文件名，大小，文件
	struct stat sbuf;
	int ret;
	char buf[1000]={0};
	off_t hadlenth;
	off_t needlenth;
	off_t sum;
	off_t total=0;
	char mdfilename[33]={0};
	int fd;
	char path[64]={0};
	strcpy(path,"./acloud/");
	
	recv_n(new_fd,mdfilename,32);//接收md5
	strcpy(mdfn,mdfilename);
	strcat(path,mdfilename);//得到md名称文件的路径
	recv_n(new_fd,&sum,sizeof(off_t));//接收文件总大小
	fd=open(path,O_RDWR|O_CREAT|O_EXCL,0666);
	if(fd==-1){
		fd=open(path,O_RDWR);
		stat(path,&sbuf);
		hadlenth=sbuf.st_size;
	}else{//创建成功，该md5不存在
		hadlenth=0;
	}
	send_n(new_fd,&hadlenth,sizeof(off_t));//发送已有大小
	*mysize=sum;
	needlenth=sum-hadlenth;
	lseek(fd,hadlenth,SEEK_SET);
	printf("recving %s,size=%ld\n",filename,needlenth);
	while(1){
		if(needlenth==0){
			ret=1;
			send_n(new_fd,&ret,sizeof(int));
			break;
		}
		if(needlenth-total<sizeof(buf)){
			ret=recv_n(new_fd,buf,needlenth-total);
		}else{
			ret=recv_n(new_fd,buf,sizeof(buf));
		}
		if(ret<0){
			printf("recv==-1的未知错误\n");
			break;
		}else if(ret==0){
			printf("客户端上传被打断\n");
			return -1;
		}else{
			write(fd,buf,ret);
			total+=ret;
			if(total==needlenth){
				ret=1;
				send_n(new_fd,&ret,sizeof(int));
				break;
			}
		}
	}
	close(fd);
	return 0;
}
