#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/epoll.h>
#include <netdb.h>
#include <errno.h>

typedef struct{
	pid_t pid;
	int fd;
	short busy;
}Data,*pData;
typedef struct{
	int len;
	char buf[1000];
}train;
void make_child(pData,int);
void child_handle(int);
void send_fd(int,int,short);
void recv_fd(int,int*,short*);
int tran_file(int);
int send_n(int,void *,size_t);
int recv_n(int,void *,size_t);
