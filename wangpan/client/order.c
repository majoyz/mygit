#include "order.h"

short judge_order(char* tmpbuf,struct order *pod){
	char ot[8]={0};
	int i=0,j=0,k=0;
	while(tmpbuf[i]==' '){//去掉命令头空格
		i++;
	}
	while(tmpbuf[i]!=' '&&tmpbuf[i]!='\n'){//截取命令
		ot[j++]=tmpbuf[i++];
	}

	//printf("%s\n",ot);
	if(!strcmp(ot,"cd")){
		pod->oid=1;
	}else if(!strcmp(ot,"ls")){
		pod->oid=2;
	}else if(!strcmp(ot,"puts")){
		pod->oid=3;
	}else if(!strcmp(ot,"gets")){
		pod->oid=4;
	}else if(!strcmp(ot,"remove")){
		pod->oid=5;
	}else if(!strcmp(ot,"pwd")){
		pod->oid=6;
	}else if(!strcmp(ot,"mkdir")){
		pod->oid=7;
	}else{
		return -1;
	}

	if(tmpbuf[i]=='\n'){//无后缀命令
		//printf("order_id=%s\n",ot);
		if(pod->oid==2||pod->oid==6){
			return pod->oid;
		}else{
			//system("clear");
			printf("该命令不可独立使用！\n");
			return -1;
		}
	}
	while(tmpbuf[i]==' '){//去掉命令间空格
		i++;
	}
	if(tmpbuf[i]=='\n'){//无后缀命令后面带了空格
		//printf("order_id=%s\n",ot);
		return pod->oid;
	}
	if(pod->oid==2||pod->oid==6){//无后缀命令带了后缀
			//system("clear");
		printf("该命令不能跟后缀！\n");
		return -1;
	}
	while(tmpbuf[i]!='\n'){//截取命令后缀
		pod->buf[k++]=tmpbuf[i++];
	}
	//printf("order_id=%s,order_buf=%s\n",ot,pod->buf);
	return pod->oid;
}

int c_gets(int sfd,char* filename,int tmpopt){//不接文件名，只接文件及大小
	int fd;
	int ret;
	int len;
	char buf[1000]={0};
	off_t sum;
	struct stat sbuf;
	off_t tmpsum;
	char tmpmd[33]={0};
	send_n(sfd,&tmpopt,sizeof(int));//发送选项
	if(tmpopt==1){
		fd=open(filename,O_RDWR|O_CREAT|O_TRUNC,0666);
	}else if(tmpopt==2){//断点下载
		fd=open(filename,O_RDWR,0666);
		stat(filename,&sbuf);
		tmpsum=sbuf.st_size;
		send_n(sfd,&tmpsum,sizeof(off_t));//发送已有大小
		lseek(fd,0,SEEK_END);//定位到文件尾断点下载
		recv_n(sfd,tmpmd,33);//接收md5码用于对比确认

	}else{
		printf("不可能出现的错误\n");
		return -1;
	}
	//recv_n(sfd,&len,4);
	recv_n(sfd,&sum,sizeof(off_t));//接收文件大小
			//system("clear");
	printf("recving %s,size=%ld\n",filename,sum);
	long one=sum/100;
	long every=0;
	long total=0;
	int i=0;
	while(1){
		if(sum==0){
			printf("100%%\n传输成功！\n");
			break;
		}
		if(sum-total<1000){
			ret=recv_n(sfd,buf,sum-total);
		}else{
			ret=recv_n(sfd,buf,sizeof(buf));
		}
		if(ret<0){
			printf("recv==-1的未知错误\n");
			break;
		}else if(ret==0){
			printf("server over\n");
			return -1;
		}else{
			write(fd,buf,ret);
			if(total+=ret,total>every){
				printf("%d%s\r",i,"%");
				rewind(stdout);
				i++;
				every+=one;
			}
			if(total==sum){
				printf("100%%\n传输成功！\n");
				break;
			}
		}
	}
//	if(tmpopt==2){
//		printf("断点下载结果检测...\n");
//		char *md=MD5()
//	}
	close(fd);
	return 0;
}

int c_puts(int sfd,char *filename){
	struct stat sbuf;
	off_t lenth;
	off_t hadlenth;
	off_t needlenth;
	off_t tmplenth;
	int ret;
	char mdfilename[33]={0};
	int le=strlen(filename);
	int gfd;
	
	getmd(filename,mdfilename);
	//puts(mdfilename);
	//printf("得到了文件的md5码如上\n");
	send_n(sfd,mdfilename,32);//发送md5
	//recv_n(sfd,&ret,sizeof(int));//接收对比结果
	//printf("接收到的对比结果ret=%d\n",ret);
	//if(ret==1){
	//	printf("秒传成功\n");
	//	return 0;
	//}else{
		gfd=open(filename,O_RDONLY);
		stat(filename,&sbuf);
		//recv_n(sfd,&ret,sizeof(int));
		lenth=sbuf.st_size;
	//	le=sizeof(lenth);
	//	printf("gfd=%d\n",gfd);
	//	printf("准备发送大小\n");
		//send_n(sfd,&le,4);
		send_n(sfd,&lenth,sizeof(off_t));//发送文件大小
	//	printf("file size=%ld\n",lenth);

		//接收服务器已有的文件大小
		recv_n(sfd,&hadlenth,sizeof(off_t));
		needlenth=lenth-hadlenth;
		printf("file needsize=%ld\n",needlenth);
		
	//	printf("准备发送文件\n");
		while(1){
			tmplenth=sendfile(sfd,gfd,&hadlenth,needlenth);//零拷贝上传文件
			if(tmplenth<needlenth){
				needlenth-=tmplenth;
				hadlenth+=tmplenth;
			}else{
				break;
			}
		}
	//	printf("after sendfile\n");
		recv_n(sfd,&le,sizeof(int));//接收最终是否成功
		if(le==1){
			printf("upload success!\n");
			close(gfd);
			return 0;
		}
		printf("upload unseccess\n");
		close(gfd);
	return 0;
}
