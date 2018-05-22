#include "func.h"

struct send{
	int flag;
	char buf[128];
};

//void sigfunc(int sig){
	//printf("输入框已关闭，请关闭此窗口")
//}

int main(){
	int shmid=shmget(1023,4096,0600|IPC_CREAT);
	struct send *p=(struct send *)shmat(shmid,NULL,0);
	//得到共享内存指针
	int semid=semget(1024,1,0600|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=+1;
	sopv.sem_flg=SEM_UNDO;
	//信号量设置
	while(1){
		//semop(semid,&sopp,1);//加锁
		while(1){
			if(p->flag==1){
				semop(semid,&sopp,1);//加锁
				puts("A:");
				//puts(p->buf);
				printf("%s\n",p->buf);
				p->flag=0;
				bzero(p->buf,sizeof(p->buf));
				semop(semid,&sopv,1);//解锁
				break;
			}else if(p->flag==2){
				semop(semid,&sopp,1);//加锁
				puts("B:");
				//puts(p->buf);
				printf("%s\n",p->buf);
				p->flag=0;
				bzero(p->buf,sizeof(p->buf));
				semop(semid,&sopv,1);//解锁
				break;
			}else if(p->flag==3){
				printf("输入框已退出，请关闭本窗口\n");
				p->flag=5;
				semctl(semid,0,IPC_RMID);
				shmdt(p);
				shmctl(shmid,IPC_RMID,0);
				return 0;
			}
		}
		//semop(semid,&sopv,1);//解锁
	}
	return 0;
}
