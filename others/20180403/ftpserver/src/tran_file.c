#include "factory.h"
void getfile(int sfd,char *p,int ui,int fi)
{
    long len;
    recv(sfd,&len,sizeof(long),0);
    char buf[20]={0};
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server="localhost";
    char *usr="root";
    char *password="3412";
    char *database="wangpan";
    char query[200]="select realname from userspace where filename=";
    sprintf(query,"%s'%s' and userID=%d and dirID=%d",query,p,ui,fi);
    int t;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,usr,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
    }
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",        mysql_error(conn));
    }else
    {
        res=mysql_use_result(conn);
        if(res)
        {
            if((row=mysql_fetch_row(res))!=NULL)
            {
                strcpy(buf,row[0]); 
            }
            else 
            {
                printf("can't find file");
                return;
            }
        } 
        mysql_free_result(res);
    }
    mysql_close(conn);
    int fd=open(buf,O_RDONLY);
    struct stat st;
    stat(buf,&st);
    long len1=st.st_size-len;
    lseek(fd,len-1,SEEK_SET);
    printf("%ld %ld\n",len,len1);
    if(sendfile(sfd,fd,0,len1)<0)
    {
        perror("sendfile");
    }
    close(fd);
}
void putfile(int sfd,char *p,int ui,int fi)
{
    char signal='1';
    send (sfd,&signal,1,0);
    char MD5[16]={0};
    char realname[20]={0};
    recv(sfd,MD5,sizeof(MD5),0);
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server="localhost";
    char *usr="root";
    char *password="3412";
    char *database="wangpan";
    char query[200]="select realname from userspace where MD5=";
    sprintf(query,"%s'%s'",query,MD5);
    int t;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,usr,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
    }
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query1:%s\n",        mysql_error(conn));
    }else
    {
        res=mysql_use_result(conn);
        if(res)
        {
            if((row=mysql_fetch_row(res))!=NULL)
            {
                strcpy(realname,row[0]);
                goto lable;
            }
        }
    }
    mysql_free_result(res);
    int fd=open(p,O_WRONLY|O_CREAT,0666);
    char buf[512]={0};
    while(1)
    {
        if(recv(sfd,buf,sizeof(buf),0)<sizeof(buf))
        {
        write(fd,buf,strlen(buf));
        bzero(buf,sizeof(buf));
        break;
        }
        write(fd,buf,strlen(buf));
        bzero(buf,sizeof(buf));
    }
    strcpy(query,"insert into userspace (dirID,MD5,userID,filename,realname) values (");
    sprintf(query,"%s%d,'%s',%d,'%s','%s')",query,fi,MD5,ui,p,p);    
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query2:%s\n",        mysql_error(conn));
    }
    return;
lable:
    
    mysql_free_result(res);
    strcpy(query,"insert into userspace (dirID,MD5,userID,filename,realname) values (");
    sprintf(query,"%s%d,'%s',%d,'%s','%s')",query,fi,MD5,ui,p,realname);
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query3:%s\n",        mysql_error(conn));
    }
    mysql_close(conn);
}
