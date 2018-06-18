#include "func.h"

struct send{
	int flag;
	char buf[128];
};

int bpid;
int fdrt;
int fdwt;
void sigfunc1(int sig){//自己关闭
	int shmid=shmget(1023,4096,0600|IPC_CREAT);
	struct send *p=(struct send *)shmat(shmid,NULL,0);
	kill(bpid,SIGQUIT);
	p->flag=3;
	//char x[128]="CLOSE";
	strcpy(p->buf,"CLOSE\0");
	shmdt(p);
	printf("\n");
	exit(0);
	//分自己关闭和收到信号关闭
		//自己关闭的话
		//给共享内存传2让A1自己关闭
		//信号量和共享内存也A1关
		//自己退出
	//收到信号的话
		//给共享内存传2让A1自己关闭
		//信号量和共享内存也A1关
		//关闭管道删除管道
		//自己退出
}
void sigfunc2(int sig){
	int shmid=shmget(1023,4096,0600|IPC_CREAT);
	struct send *p=(struct send *)shmat(shmid,NULL,0);
	p->flag=3;
	strcpy(p->buf,"CLOSE\0");
	shmdt(p);
	close(fdwt);
	close(fdrt);
	unlink("1in");
	unlink("2in");
	printf("对方已断开连接\n");
	exit(0);
}

int main(){
	char *argv1="1in";
	char *argv2="2in";
//	unlink(argv1);
//	unlink(argv2);
	if(mkfifo(argv1,0666)==-1){
//		perror("mkfifo");
//		return -2;
	}
	if(mkfifo(argv2,0666)==-1){
//		perror("mkfifo");
//		return -2;
	}
	//管道建立
	int shmid=shmget(1023,4096,0600|IPC_CREAT);
	struct send *p=(struct send *)shmat(shmid,NULL,0);
	//得到共享内存指针
	int fdr=open(argv2,O_RDONLY);//没有O_NONBLOCK时会阻塞到对面对应的写端打开为止，写端同理
	if(fdr==-1){
		perror("open1");
		return -1;
	}
	int fdw=open(argv1,O_WRONLY);
	if(fdw==-1){
		perror("open2");
		return -1;
	}
	fdrt=fdr;
	fdwt=fdw;
	printf("准备完毕！请输入！\n");
	//准备完毕	
	p->flag=0;
	bzero(p->buf,sizeof(p->buf));
	//共享内存初始化
	int semid=semget(1024,1,0600|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=+1;
	sopv.sem_flg=SEM_UNDO;
	//信号量配置
	char tmpbuf[128]={0};
	fd_set readfds;
	int gs;
	
	int apid=getpid();
	//int bpid;
	write(fdw,&apid,sizeof(int));
	read(fdr,&bpid,sizeof(int));
	printf("apid=%d,bpid=%d\n",apid,bpid);
	//pid发送与接收
	signal(SIGINT,&sigfunc1);
	signal(SIGQUIT,&sigfunc2);
	//信号捕捉
	while(1){
		FD_ZERO(&readfds);
		FD_SET(0,&readfds);
		FD_SET(fdr,&readfds);
		//select设置
		gs=select(fdr+1,&readfds,NULL,NULL,NULL);
		if(gs>0){//select监测到
			if(FD_ISSET(fdr,&readfds)){
				bzero(tmpbuf,sizeof(tmpbuf));
				int ret=read(fdr,tmpbuf,sizeof(tmpbuf));
				if(ret==-1){
					perror("read");
					return -3;
				}else if(ret==0){
					printf("baoliuwenti\n");
					break;
				}
				semop(semid,&sopp,1);//加锁
				while(1){
					if(p->flag==0){
						strcpy(p->buf,tmpbuf);
						p->flag=2;
						break;
					}
				}
				//puts(tmpbuf);
				semop(semid,&sopv,1);//解锁
			}
			if(FD_ISSET(0,&readfds)){
				bzero(tmpbuf,sizeof(tmpbuf));
				int ret2=read(0,tmpbuf,sizeof(tmpbuf)-1);
				if(ret2==0){
					printf("baoliu\n");
					break;
				}
				write(fdw,tmpbuf,strlen(tmpbuf)-1);
				semop(semid,&sopp,1);//加锁
				while(1){
					if(p->flag==0){
						strncpy(p->buf,tmpbuf,strlen(tmpbuf)-1);
						p->flag=1;
						break;
					}
				}
				semop(semid,&sopv,1);//解锁
			}
		}
	}
	//close(fdr);
	//close(fdw);
	//unlink(argv1);
	//unlink(argv2);

	return 0;
}
