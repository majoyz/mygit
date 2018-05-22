#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
//输入一个文件的相对路径，广度优先遍历其中所有文件
//程序 通过一个链队列（即用链表头部出队列和链表尾插法入队列） 路径树的层遍历

//链队列结构体，存储 绝对路径名
typedef struct Node{
	char name_dir[256];
	struct Node* next; 
}Dir,*pDir;
void printdir(char*,pDir*,pDir*);
//尾插法入队列
void List_tail_insert(pDir* pphead,pDir* pptail,const char* name_dir)
{
	pDir pnew=(pDir)malloc(sizeof(Dir));
	strcpy(pnew->name_dir,name_dir);
	pnew->next=NULL;
	if((*pphead)==NULL)
	{
		(*pphead)=pnew;
		(*pptail)=pnew;
		return ;
	}
	(*pptail)->next=pnew;
	(*pptail)=pnew;
	return ;
}
//从头部出队列，用name_dir存储出队列节点的信息
void Pop_queue(pDir* pphead,pDir* pptail,char* name_dir)
{
	pDir ptmp=(*pphead);
	strcpy(name_dir,(*pphead)->name_dir);
	if((*pphead)==(*pptail))
	{
		(*pphead)=NULL;
		free((*pptail));
		(*pptail)=NULL;
		return ;
	}
	(*pphead)=ptmp->next;
	free(ptmp);
	return ;
}
//主函数
int main(int argc,char*argv[])
{
	pDir phead=NULL;
	pDir ptail=NULL;
	char tmp_dir[256]={0};
	if(2!=argc)
	{
		printf("argc!=3,%d\n",argc);
		return -1;
	}
	//先将第一个路径作为种子节点插入队列
	List_tail_insert(&phead,&ptail,argv[1]);
	//开始广度遍历，不断出入队列，队列为空终止
	while(phead)
	{
		Pop_queue(&phead,&ptail,tmp_dir);
		printf("%s",tmp_dir);
		printdir(tmp_dir,&phead,&ptail);
	}
	return 0;

}
//访问出队列节点，即出队列的目录节点，满足为目录的文件入队列
void printdir(char* path,pDir* pphead,pDir* pptail)
{
	DIR* d=opendir(path);
	if(NULL==d)
	{
		perror("opendir");
		return ;
	}
	struct dirent * p;
	char  buf[256]={0};
	while(p=readdir(d))
	{
		if(strcmp(p->d_name,".")==0||strcmp(p->d_name,"..")==0)
		{
		}else{
			if(strcmp("/",path)==0)
			{  
				sprintf(buf,"/%s",p->d_name);
				puts(buf);
			}else{
				sprintf(buf,"%s/%s",path,p->d_name);
				puts(buf);
			}
			if(p->d_type==4)
			{
			//	sprintf(buf,"%s/%s",path,p->d_name);
				List_tail_insert(pphead,pptail,buf);
			}
		}
	}
	closedir(d);
}
