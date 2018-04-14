#include "head.h"
#include "tran_n.h"

struct ls_data{//ls命令用结构体
	char mod;
	char name[128];
	long len;
};

int usrnamesame(char *);
int myregister(int);
int login(int,char*);
int get_procode(int*);
int listnamesame(int*,char*,char*);
int s_ls(int,struct ls_data*,int,char*);
int logging(char*,char*);
int get_mdfilename(char*,char*,int,char*);
int mdsame(char*,off_t*);
int insert_file(int,char*,char*,char*,off_t,char);
int delete_file(int,char*,char*);
