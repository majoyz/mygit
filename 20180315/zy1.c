#include "func.h"
#define N 10000000

int main(){
	key_t key=ftok("./zy1.c",1);
	int shmid=shmget(key,4096,0600|IPC_CREAT);
	int *p=(int *)shmat(shmid,NULL,0);
	p[0]=0;

	int semid=semget(1025,1,0600|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=+1;
	sopv.sem_flg=SEM_UNDO;

	struct timeval tm1,tm2;
	gettimeofday(&tm1,NULL);

	if(!fork()){
		for(int i=0;i<N;i++){
			semop(semid,&sopp,1);
			p[0]+=1;
			semop(semid,&sopv,1);
		}
	}else{
		for(int i=0;i<N;i++){
			semop(semid,&sopp,1);
			p[0]+=1;
			semop(semid,&sopv,1);
		}
		wait(NULL);
		gettimeofday(&tm2,NULL);
		printf("p[0]=%d\n",p[0]);
		printf("usetime=%liusec",tm2.tv_sec*1000000-tm1.tv_sec*1000000+tm2.tv_usec-tm1.tv_usec);
		semctl(semid,0,IPC_RMID);
		shmdt(p);
		shmctl(shmid,IPC_RMID,NULL);
		return 0;
	}
}
