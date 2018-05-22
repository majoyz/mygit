#include "func.h"

typedef struct msgbuf{
	long mtype;
	char mtext[64];
}mb;

int main(){
	int msgid=msgget(1024,0600|IPC_CREAT);
	mb snd,rcv;
	if(!fork()){
		printf("I'm child,I'll receive\n");
		rcv.mtype=1;
		msgrcv(msgid,&rcv,sizeof(rcv.mtext),1,0);
		printf("%d\n",*(int *)rcv.mtext);
	}else{
		printf("I'm father,I'll send\n");
		snd.mtype=1;
		int n=50;
		memcpy(snd.mtext,&n,sizeof(int));
		msgsnd(msgid,&snd,1,0);
		wait(NULL);
		msgctl(msgid,IPC_RMID,NULL);
		return 0;
	}
}
