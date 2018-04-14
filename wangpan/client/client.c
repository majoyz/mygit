#include "order.h"

int main(int argc,char *argv[]){
	if(argc!=3){
		printf("./client ip port\n");
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(ret==-1){
		perror("connect");
		return -1;
	}
	
begin:
	printf("注册请输入0，登录请输入1：\n");
	scanf("%d",&ret);
	getchar();
	send_n(sfd,&ret,sizeof(int));
	if(ret==0){
	while(1){
		ret=myregister(sfd);
		if(ret==0){
			ret=1;
			break;
		}
	}
	}
	if(ret==1){
		while(1){
			ret=login(sfd);
			if(ret==0){
				break;
			}
		}
	}else{
		printf("请输入正确的指令！\n");
		goto begin;
	}
	printf("用户访问成功!请输入指令：\n");

	struct order od;//send的命令结构体
	char tmpbuf[OLEN]={0};//暂存输入的命令
	struct ls_data lsdata;
	int tmpfd;
	int tmpnum;
	int tmpopt=0;
	size_t tmplen;
	while(1){
		bzero(&od,sizeof(od));
		fgets(tmpbuf,OLEN,stdin);
		system("clear");
		ret=judge_order(tmpbuf,&od);//判断命令单独封装
		if(ret==-1){
			printf("命令输入错误\n");
			continue;
		}
		//continue;//增量编写测试点


		if(od.oid==3){
			tmpfd=open(od.buf,O_RDONLY);
			if(tmpfd==-1){
				printf("本地文件不存在！\n");
				continue;
			}else{
				close(tmpfd);
			}
		}
		if(od.oid==4){
			tmpfd=open(od.buf,O_RDONLY);
			if(tmpfd!=-1){
				printf("文件名在本地已存在！\n");
				printf("请选择：1覆盖，2继续下载，3退出\n");
				scanf("%d",&tmpopt);
				getchar();
				if(tmpopt!=1&&tmpopt!=2&&tmpopt!=3){
					printf("请输入正确的指令！\n");
					close(tmpfd);
					continue;
				}else if(tmpopt==3){
					close(tmpfd);
					continue;
				}
			}else{
				tmpopt=1;
			}
		}

		send(sfd,&od,sizeof(od),0);//发命令结构体给服务器
		int ok=0;
		recv(sfd,&ok,sizeof(int),0);//接收服务器执行成败情况
		if(ok==-1){
			if(od.oid==3){
				printf("文件名已存在\n");
			}else if(od.oid==7){
				printf("目录名已存在\n");
			}else{
				printf("路径不存在！\n");
			}
			continue;
		}else if(ok==0){
			printf("糟糕，与服务器的连接中断了\n");
			return -1;
		}
		switch("%hd",od.oid){
			case 1://cd
				bzero(&tmpbuf,sizeof(tmpbuf));
				recv_n(sfd,&tmplen,sizeof(size_t));
				recv_n(sfd,tmpbuf,tmplen);//客户端火车接收地址
				printf("%s\n",tmpbuf);
				break;
			case 2://ls
				recv_n(sfd,&tmpnum,sizeof(int));
				if(tmpnum==1){
					printf("total %d file\n",tmpnum);
				}else{
					printf("total %d files\n",tmpnum);
				}
				while(tmpnum){
					ret=recv(sfd,&lsdata,sizeof(lsdata),0);
					printf("%c %20s %20ld\n",lsdata.mod,lsdata.name,lsdata.len);
					tmpnum--;
				}
				break;
			case 3://puts
				printf("准备上传...\n");
				c_puts(sfd,od.buf);
				break;
			case 4://gets
				printf("准备下载...\n");
				ret=c_gets(sfd,od.buf,tmpopt);
				if(-1==ret){
					printf("error gets");
				}
				break;
			case 5://remove
				printf("删除成功！\n");
				break;
			case 6://pwd
				bzero(&tmpbuf,sizeof(tmpbuf));
				recv(sfd,&tmpbuf,sizeof(tmpbuf),0);
				printf("%s\n",tmpbuf);
				break;
			case 7:
				printf("创建成功！\n");
				break;
			default:
				printf("预料之外的错误\n");
				break;
		}
	}
}
