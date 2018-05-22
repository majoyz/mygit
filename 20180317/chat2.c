#include "func.h"

struct msgbuf{
	long mtype;
	char mtext[128];
};

int apid;
int fdrt;
int fdwt;
void sigfunc1(int sig){
	//zijiguan
	kill(apid,SIGQUIT);
	struct msgbuf in;
	int msgid=msgget(1025,0600|IPC_CREAT);
	in.mtype=3;
	strcpy(in.mtext,"CLOSE\0");
	msgsnd(msgid,&in,sizeof(in.mtext),0);
	printf("\n");
	exit(0);
}
void sigfunc2(int sig){
	//shouxinhaoguan
	struct msgbuf in;
	int msgid=msgget(1025,0600|IPC_CREAT);
	in.mtype=3;
	strcpy(in.mtext,"CLOSE\0");
	msgsnd(msgid,&in,sizeof(in.mtext),0);
	close(fdrt);
	close(fdwt);
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
	int fdw=open("2in",O_WRONLY);
	if(fdw==-1){
		perror("open");
		return -1;
	}
	int fdr=open("1in",O_RDONLY);
	if(fdr==-1){
		perror("open");
		return -1;
	}
	fdrt=fdr;
	fdwt=fdw;
	printf("准备完毕！请输入！\n");
	//建立并打开管道
	int msgid=msgget(1025,0600|IPC_CREAT);
	//char msg[128];
	struct msgbuf in;
	//消息队列
	//信号捕捉等等再说
	int semid=semget(1026,1,0600|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=+1;
	sopv.sem_flg=SEM_UNDO;
	//信号量
	char tmpbuf[128]={0};
	//暂存字符数组

	//int apid;
	int bpid=getpid();
	write(fdw,&bpid,sizeof(int));
	read(fdr,&apid,sizeof(int));
	printf("apid=%d,bpid=%d\n",apid,bpid);
	//获得pid
	signal(SIGINT,sigfunc1);
	signal(SIGQUIT,sigfunc2);
	//信号捕捉
	while(1){
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(0,&readfds);
		FD_SET(fdr,&readfds);
		int gs=select(fdr+1,&readfds,NULL,NULL,NULL);
		//select设置
		if(gs>0){
			if(FD_ISSET(fdr,&readfds)){
				bzero(tmpbuf,sizeof(tmpbuf));
				int ret=read(fdr,tmpbuf,sizeof(tmpbuf));
				if(ret==-1){
					perror("read");
					return -3;
				}else if(ret==0){
					printf("baoliu\n");
					break;
				}
				semop(semid,&sopp,1);//加锁
				in.mtype=1;
				strcpy(in.mtext,tmpbuf);
				msgsnd(msgid,&in,strlen(in.mtext),0);
				semop(semid,&sopv,1);//解锁
				//puts(tmpbuf);
			}
			if(FD_ISSET(0,&readfds)){
				bzero(tmpbuf,sizeof(tmpbuf));
				int ret2=read(0,tmpbuf,sizeof(tmpbuf)-1);
				if(ret2==0){
					printf("baoliu");
					break;
				}
				write(fdw,tmpbuf,strlen(tmpbuf)-1);
				semop(semid,&sopp,1);//加锁
				in.mtype=2;
				strcpy(in.mtext,tmpbuf);
				msgsnd(msgid,&in,strlen(in.mtext),0);
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
