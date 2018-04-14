#include "dosql.h"
#define UNLEN 16
#define SALTLEN 12
#define PWLEN 16
//#define MMLEN 100

int logging(char *username,char *action){//日志记录
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="insert into logs(username,action,time) values ('";
	sprintf(query,"%s%s%s%s%s",query,username,"','",action,"',now())");
	int t,ret;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("log insert success\n");
	}
	mysql_close(conn);
	return 0;
}

int insert_file(int procode,char *filename,char *mdfilename,char *username,off_t mysize,char type){//上传文件puts
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	if(type=='d'){
		mysize=4096;
	}
	char query[300]="insert into file(procode,name,type,md,username,size) values (";
	sprintf(query,"%s%d%s%s%s%c%s%s%s%s%s%ld%s",query,procode,",'",filename,"','",type,"','",mdfilename,"','",username,"',",mysize,")");
	puts(query);
	int t,ret;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("file insert success\n");
	}
	mysql_close(conn);
	return 0;
}

int delete_file(int procode,char*filename,char *username){//删除文件delete
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="delete from file where procode=";
	char querys[300]="select * from file where procode=";
	sprintf(querys,"%s%d%s%s%s%s%s",querys,procode," and name='",filename,"' and username='",username,"' and type='-'");
	sprintf(query,"%s%d%s%s%s%s%s",query,procode," and name='",filename,"' and username='",username,"' and type='-'");
	//puts(query);
	int s,t,ret;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	puts(querys);
	s=mysql_query(conn,querys);
	if(s){
		printf("Error making query:%s\n",mysql_error(conn));
		ret=-1;
	}else{
		res=mysql_store_result(conn);
		printf("查结果数之前\n");
		ret=mysql_num_rows(res);
		printf("查到结果数为%d\n",ret);
		if(ret==0){
			mysql_free_result(res);
			mysql_close(conn);
			return -1;
		}else{
			mysql_free_result(res);
			//mysql_close(conn);
			puts(query);
			t=mysql_query(conn,query);
			if(t){
				printf("Error making query:%s\n",mysql_error(conn));
				mysql_close(conn);
				return -1;
			}else{
				printf("delete success\n");
				mysql_close(conn);
				return 1;
			}
		}
	}
}

int get_procode(int *pcode){//cd命令处理..用，获取procode
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="select procode from file where code=";
	sprintf(query,"%s%d",query,*pcode);
	puts(query);
	int t,ret;
	conn=mysql_init(NULL);//获得一个MYSQL类型
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))//与数据库建立连接并绑定到conn
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);
		*pcode=atoi(row[t]);
		mysql_free_result(res);
		mysql_close(conn);
		return 0;
	}
}

int mdsame(char *mdfilename,off_t *mysize){//判断秒传puts
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="select size from file where md='";
	sprintf(query,"%s%s%s",query,mdfilename,"'");
	puts(query);
	int t,ret;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_store_result(conn);
		if(res){
			row=mysql_fetch_row(res);
			if(row==NULL){
				mysql_free_result(res);
				mysql_close(conn);
				return -1;
			}else{
				*mysize=atoi(row[t]);
				mysql_free_result(res);
				mysql_close(conn);
				return 1;
			}
		}
	}
}

int listnamesame(int *pcode,char *listname,char *username){//判断该路径是否存在，是则更改pcode，cd命令用
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="select code from file where procode=";
	sprintf(query,"%s%d%s%s%s%s%s",query,*pcode," and type='d' and name='",listname,"' and username='",username,"'");
	puts(query);
	int t,ret;
	conn=mysql_init(NULL);//获得一个MYSQL类型
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_store_result(conn);
		if(res){
			row=mysql_fetch_row(res);
			if(row==NULL){
				mysql_free_result(res);
				mysql_close(conn);
				printf("目录不存在\n");
				return -1;
			}else{
				*pcode=atoi(row[t]);
				mysql_free_result(res);
				mysql_close(conn);
				printf("目录存在\n");
				return 1;
			}
		}
	}
}

int s_ls(int new_fd,struct ls_data *lsdata,int procode,char *username){//ls命令，内含传输功能
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="select type,name,size from file where procode=";
	sprintf(query,"%s%d%s%s%s",query,procode," and username='",username,"'");
	puts(query);
	int t,r=0,ret;
	conn=mysql_init(NULL);//获得一个MYSQL类型
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_store_result(conn);
		ret=mysql_num_rows(res);//行数，即ls到的结果数
		printf("I'll send %d\n",ret);
		send_n(new_fd,&ret,sizeof(int));
		if(res){
			while((row=mysql_fetch_row(res))!=NULL){
				strcpy(&lsdata->mod,row[r++]);
				strcpy(lsdata->name,row[r++]);
				lsdata->len=atoi(row[r++]);
				send_n(new_fd,lsdata,sizeof(struct ls_data));
				bzero(lsdata,sizeof(struct ls_data));
				r=0;
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}

int get_mdfilename(char *filename,char *mdfilename,int procode,char *username){//判断有没有可供下载的同名文件并获取MD5文件名gets，
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="select md from file where name='";
	sprintf(query,"%s%s%s%d%s%s%s",query,filename,"' and procode=",procode," and username='",username,"' and type='-'");
	puts(query);
	int t,ret;
	conn=mysql_init(NULL);//获得一个MYSQL类型
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)){
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t){
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_store_result(conn);
		if(res){
			ret=mysql_num_rows(res);
			printf("ret=%d\n",ret);
			if(ret==0){//文件名还不在服务器上
				ret=-1;
			}else{//文件名已经在服务器上了
				row=mysql_fetch_row(res);
				strcpy(mdfilename,row[t]);
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return ret;
}

int usrnamesame(char *usrname){//判断用户名是否已经被注册
	MYSQL *conn;MYSQL_RES *res;MYSQL_ROW row;
	char* server="localhost";char* user="root";
	char* password="12345";char* database="wangdao";
	char query[300]="select * from usrs where username='";
	sprintf(query,"%s%s%s",query,usrname,"'");
	//strcpy(query,"select * from usrs");
	puts(query);
	int t,ret;
	conn=mysql_init(NULL);//获得一个MYSQL类型
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))//与数据库建立连接并绑定到conn
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_store_result(conn);
		if(res){
			ret=mysql_num_rows(res);
			printf("ret=%d\n",ret);
			if(ret!=0){
				ret=-1;
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return ret;
}

int get_salt(char *salt){
	//随机产生8次随机数
	char *str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	srand((unsigned int)time((time_t *)NULL));//使用系统时间来初始化随机数发生器
	for(int i=0;i<8;i++){
		salt[i+3]=str[(rand()%62)];
	}
	return 0;
}

int save_usr(char *usrname,char *salt,char *p){//注册成功
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="12345";
	char* database="wangdao";
	char query[200]="insert into usrs(username,salt,password) values('";
	sprintf(query,"%s%s%s%s%s%s%s",query,usrname,"','",salt,"','",p,"')");
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("insert success\n");
	}
	mysql_close(conn);
	return 0;
}

int get_salt2(char *usrname,char *salt){//从数据库里拿盐值，登陆时用
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="12345";
	char* database="wangdao";
	char query[300]="select salt from usrs where username='";
	sprintf(query,"%s%s%s",query,usrname,"'");
	int t,ret;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);
		strcpy(salt,row[t]);
		mysql_free_result(res);
		mysql_close(conn);
		return 0;
	}
}

int cmp_usr(char *usrname,char *p){//对比密文，登陆时用
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="12345";
	char* database="wangdao";
	char query[300]="select password from usrs where username='";
	sprintf(query,"%s%s%s",query,usrname,"'");
	int t,ret;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);
		if(strcmp(p,row[t])==0){
			mysql_free_result(res);
			mysql_close(conn);
			return 0;
		}else{
			mysql_free_result(res);
			mysql_close(conn);
			return -1;
		}
	}
}

int myregister(int new_fd){//服务器注册主函数
	size_t tmplen;
	int ret;
	char salt[SALTLEN]={'$','6','$'};
	char usrname[UNLEN]={0};
	char *p;
	ret=recv_n(new_fd,&tmplen,sizeof(size_t));
	if(ret==0){
		return -2;
	}
	ret=recv_n(new_fd,usrname,tmplen);//接收用户名火车
	if(ret==0){
		return -2;
	}
	puts(usrname);
	ret=usrnamesame(usrname);//判断用户名重复
	send_n(new_fd,&ret,sizeof(int));//发送判断结果
	if(ret==-1){
		return -1;
	}

	//盐值生成
	get_salt(salt);
	//盐值生成

	send_n(new_fd,&salt,SALTLEN);//发送盐值
	ret=recv_n(new_fd,&tmplen,sizeof(size_t));
	if(ret==0){
		return -2;
	}
	p=(char*)calloc(tmplen,sizeof(char));
	ret=recv_n(new_fd,p,tmplen);//接收密文火车
	if(ret==0){
		return -2;
	}
	puts(p);

	//入库用户数据
	puts(usrname);
	ret=save_usr(usrname,salt,p);
	//ret=0;
	send_n(new_fd,&ret,sizeof(int));//发送判断结果
	if(ret==-1){
		free(p);
		return -1;
	}
	//入库用户数据
	free(p);
	return 0;
}

int login(int new_fd,char *usrname){//服务器登陆主函数
	size_t tmplen;
	int ret;
	char salt[SALTLEN]={'$','6','$'};
	char *p;
	ret=recv_n(new_fd,&tmplen,sizeof(size_t));
	if(ret==0){
		return -2;
	}
	ret=recv_n(new_fd,usrname,tmplen);//接收用户名火车
	if(ret==0){
		return -2;
	}
	ret=usrnamesame(usrname);//判断用户名重复
	send_n(new_fd,&ret,sizeof(int));//发送判断结果
	if(ret==0){
		return -1;
	}
	get_salt2(usrname,salt);
	send_n(new_fd,&salt,SALTLEN);//发送盐值
	ret=recv_n(new_fd,&tmplen,sizeof(size_t));
	if(ret==0){
		return -2;
	}
	p=(char*)calloc(tmplen,sizeof(char));
	ret=recv_n(new_fd,p,tmplen);//接收密文火车
	if(ret==0){
		return -2;
	}
	puts(p);
	ret=cmp_usr(usrname,p);//就这句不一样
	send_n(new_fd,&ret,sizeof(int));//发送判断结果
	if(ret==-1){
		free(p);
		return -1;
	}
	free(p);
	return 0;
}
