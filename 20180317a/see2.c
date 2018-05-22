#include "func.h"

struct msgbuf{
	long mtype;
	char mtext[128];
};

int main(){
	struct msgbuf in;
	int msgid=msgget(1025,0600|IPC_CREAT);
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
	while(1){
		semop(semid,&sopp,1);//加锁
		
			memset(&in,0,sizeof(in));
			msgrcv(msgid,&in,sizeof(in),0,0);
			if(in.mtype==1){
				puts("A:");
				printf("%s\n",in.mtext);
				continue;
			}else if(in.mtype==2){
				puts("B:");
				printf("%s",in.mtext);
				continue;
			}else if(in.mtype==3){
				printf("输入结束，窗口关闭\n");
				semctl(semid,0,IPC_RMID);
				msgctl(msgid,IPC_RMID,NULL);
				return 0;
			}
		semop(semid,&sopv,1);//解锁
	}
	return 0;
}
