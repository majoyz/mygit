#include "factory.h"

void* thread_handle(void *p){
	pfac pf=(pfac)p;
	int log;
	int ret;
	char work_dir[128]={'~'};
	struct ls_data lsdata;
	int i;
	char tmpbuf[128]={0};
	int le;
	int tmpcode;
	char username[20]={0};
	char mdfilename[33]={0};
	char mdfn[33]={0};
	off_t mysize;
	int procode=0;//当前工作路径的code，与当前工作路径同改
	pque_t pq=&pf->que;
	pnode_t pcur;
	while(1){
		pthread_mutex_lock(&pq->que_mutex);
		if(!pq->que_size){
			pthread_cond_wait(&pf->cond,&pq->que_mutex);
		}
		que_get(pq,&pcur);
		pthread_mutex_unlock(&pq->que_mutex);
		//连接到一个客户端，循环接收命令了
begin:
		ret=recv_n(pcur->new_fd,&log,sizeof(int));
		if(ret==0){
			goto end;
		}
		printf("log=%d\n",log);
		if(log==0){
		while(1){
			ret=myregister(pcur->new_fd);
			if(ret==0){
				log=1;
				break;
			}else if(ret==-2){
				goto end;
			}
		}
		}
		if(log==1){
			printf("要登录\n");
			while(1){
				ret=login(pcur->new_fd,username);
				if(ret==0){
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s","login");
					logging(username,tmpbuf);
					break;
				}else if(ret==-2){
					goto end;
				}
			}
		}else{
			goto begin;
		}
		//注册函数或登陆函数

		while(1){
			struct order od;//子线程里存下每次的命令结构体
			bzero(&od,sizeof(od));
			ret=recv_n(pcur->new_fd,&od,sizeof(od));//接收命令结构体
			if(ret==0){
				break;
			}
			switch(od.oid){
				case 1://cd
					ret=s_cd(pcur->new_fd,&procode,od.buf,work_dir,username);
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","cd ",od.buf);
					logging(username,tmpbuf);
					break;
				case 2://ls
					ret=1;
					send(pcur->new_fd,&ret,sizeof(int),0);
					s_ls(pcur->new_fd,&lsdata,procode,username);
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","ls ",work_dir);
					logging(username,tmpbuf);
					break;
				case 3://puts
					//不再判断重名问题，在入库时试试重命名
					ret=1;
					send_n(pcur->new_fd,&ret,sizeof(int));
					ret=s_puts(pcur->new_fd,od.buf,mdfn,&mysize);
					if(ret!=-1){

					//循环查重名与改名
						le=strlen(od.buf);
						i=1;
						while(1){
							ret=get_mdfilename(od.buf,mdfilename,procode,username);
							if(ret==-1){
								insert_file(procode,od.buf,mdfn,username,mysize,'-');
								break;
							}else{
								if(0==strcmp(mdfn,mdfilename)){
									break;
								}else{
									od.buf[le]='(';
									od.buf[le+1]=i+48;
									od.buf[le+2]=')';
									i++;
								}
							}
						}
					}
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","puts ",od.buf);
					logging(username,tmpbuf);
					break;
				case 4://gets
					//查找库里有没有，获取MD5
					ret=get_mdfilename(od.buf,mdfilename,procode,username);
					send_n(pcur->new_fd,&ret,sizeof(int));
					if(ret==-1){//库里没查到
						break;
					}
					s_gets(pcur->new_fd,mdfilename);
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","gets ",od.buf);
					logging(username,tmpbuf);
					break;
				case 5://remove
					printf("delete\n");
					ret=delete_file(procode,od.buf,username);
					printf("delete ret=%d\n",ret);
					send(pcur->new_fd,&ret,sizeof(int),0);
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","remove ",work_dir);
					logging(username,tmpbuf);
					break;
				case 6://pwd
					ret=1;
					send(pcur->new_fd,&ret,sizeof(int),0);
					send(pcur->new_fd,&work_dir,strlen(work_dir),0);
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","pwd ",work_dir);
					logging(username,tmpbuf);
					break;
				case 7:
					tmpcode=procode;
					ret=listnamesame(&tmpcode,od.buf,username);
					if(ret==-1){
						ret=1;
					}else if(ret==1){
						printf("重名判断\n");
						ret=-1;
					}
					send(pcur->new_fd,&ret,sizeof(int),0);
					if(ret==-1){
						break;
					}
					insert_file(procode,od.buf,mdfn,username,mysize,'d');
					bzero(tmpbuf,sizeof(tmpbuf));
					sprintf(tmpbuf,"%s%s","mkdir ",od.buf);
					logging(username,tmpbuf);
					break;
				default:
					printf("理论上不应出现的错误\n");
					break;
			}
		}
end:
		close(pcur->new_fd);
		free(pcur);
		printf("client over\n");
	}
}

int main(int argc,char *argv[]){
	if(argc!=5){
		printf("./server IP PORT THREAD_NUM CAPACITY\n");
		return -1;
	}
	fac f;
	bzero(&f,sizeof(fac));
	f.pthread_num=atoi(argv[3]);
	int capacity=atoi(argv[4]);
	factory_init(&f,thread_handle,capacity);
	int sfd;
	int ret=sock_init(argv[1],argv[2],&sfd,100);//封装socket服务器端的一系列函数
	if(ret==-1){
		printf("error sock_init\n");
		return -1;
	}

	//拟加入退出机制的地方，主进程fork子进程
	
	factory_start(&f);//申请所有子线程

	int new_fd;
	pnode_t pnew;
	pque_t pq=&f.que;
	while(1){
		new_fd=accept(sfd,NULL,NULL);
		printf("I got %d\n",new_fd);
		pnew=(pnode_t)calloc(1,sizeof(node_t));
		pnew->new_fd=new_fd;
		pthread_mutex_lock(&pq->que_mutex);
		que_set(pq,pnew);
		pthread_mutex_unlock(&pq->que_mutex);
		pthread_cond_signal(&f.cond);
	}//在线程函数里接收命令结构体
}
