#include "func.h"

int main(){
	key_t key=ftok("./zy2.c",1);
	int shmid=shmget(key,4096,0600|IPC_CREAT);
	if(!fork()){
		char *p=(char *)shmat(shmid,NULL,0);
		char buf[64]="How are you";
		strcpy(p,buf);
		shmdt(p);
	}else{
		char *p=(char *)shmat(shmid,NULL,0);
		wait(NULL);
		puts(p);
		shmdt(p);
		int ret=shmctl(shmid,IPC_RMID,NULL);
		if(-1==ret){
			perror("shmctl");
			return -1;
		}
	}
	return 0;
}
