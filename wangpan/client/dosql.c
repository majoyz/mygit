#include "dosql.h"
#define UNLEN 16
#define SALTLEN 12
#define PWLEN 16
//#define MMLEN 100

int myregister(int sfd){//客户端注册函数
	size_t tmplen;
	int ret;
	char *passwd;//[PWLEN]={0};
	char salt[SALTLEN]={0};
	char usrname[UNLEN]={0};
	char c;
	//char p[MMLEN]={0};
	printf("欢迎注册！\n");
	printf("请输入用户名：\n");
	fgets(usrname,UNLEN,stdin);
	//setbuf(stdin,NULL);
	printf("usrnamelen=%ld\n",strlen(usrname));
	if(usrname[UNLEN-2]!=0&&usrname[UNLEN-2]!='\n'){
		printf("用户名最长%d个字节\n",UNLEN-2);
		while ((c=getchar())!=EOF&&c!='\n');//不停地使用getchar()获取缓冲中字符，直到获取的c是“\n”或文件结尾符EOF为止
		return -1;
	}
	usrname[strlen(usrname)-1]=0;//去除回车
	//用户名本地规则判断
	//puts(usrname);
	tmplen=strlen(usrname);
	send_n(sfd,&tmplen,sizeof(size_t));
	send_n(sfd,usrname,tmplen);//火车发送用户名
	recv_n(sfd,&ret,sizeof(int));//接收用户名判断
	if(ret==-1){
		printf("用户名已存在\n");
		return -1;
	}else{
		printf("用户名可用\n");
	}
	recv_n(sfd,&salt,SALTLEN);//接收盐值
	//puts(salt);
getpass:
	passwd=getpass("请输入密码");
	//密码本地规则判断
	if(strlen(passwd)>PWLEN-2){
		printf("密码最长%d个字节\n",PWLEN-2);
//		while ((c=getchar())!=EOF&&c!='\n');//不停地使用getchar()获取缓冲中字符，直到获取的c是“\n”或文件结尾符EOF为止
		goto getpass;
	}
	char *p=crypt(passwd,salt);
	//puts(p);
	tmplen=strlen(p);
	send_n(sfd,&tmplen,sizeof(size_t));
	send_n(sfd,p,tmplen);//火车发送密文
	recv_n(sfd,&ret,sizeof(int));//接收成败判断
	if(ret==-1){
		printf("用户名创建失败\n");
		return -1;
	}
	return 0;
}

int login(int sfd){
	size_t tmplen;
	int ret;
	char *passwd;//[PWLEN]={0};
	char salt[SALTLEN]={0};
	char usrname[UNLEN]={0};
	printf("欢迎登录！\n");
	printf("请输入用户名：\n");
	rewind(stdin);
	fgets(usrname,UNLEN,stdin);
	usrname[strlen(usrname)-1]=0;//去除回车
	tmplen=strlen(usrname);
	send_n(sfd,&tmplen,sizeof(size_t));
	send_n(sfd,usrname,tmplen);//火车发送用户名
	recv_n(sfd,&ret,sizeof(int));//接收用户名判断
	if(ret==0){//改成用户名不存在，看看能否用同一个函数
		printf("用户名不存在\n");
		return -1;
	}
	recv_n(sfd,&salt,SALTLEN);//接收盐值
	//puts(salt);
	passwd=getpass("请输入密码");
	char *p=crypt(passwd,salt);
	//puts(p);
	tmplen=strlen(p);
	send_n(sfd,&tmplen,sizeof(size_t));
	send_n(sfd,p,tmplen);//火车发送密文
	recv_n(sfd,&ret,sizeof(int));//接收对比成败判断
	if(ret==-1){
		printf("用户密码错误\n");
		return -1;
	}
	return 0;
}
