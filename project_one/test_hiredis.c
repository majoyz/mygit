///
/// @file    test_hiredis.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-16 14:31:42
///

#include <stdio.h>
#include <string.h>
#include <stddef.h>  
#include <stdarg.h>  
#include <string.h>  
#include <assert.h>  
#include <hiredis/hiredis.h> //redis C接口库

#define REDIS_HOST        "127.0.0.1"
#define REDIS_PORT        6379

void redis_cli()
{
	redisContext *c = NULL;
	redisReply      *r = NULL;

	/*连接redis数据库*/
	c = redisConnect(REDIS_HOST, REDIS_PORT);
	if(NULL == c) {
		printf("connect redis server failure\n");
		return;
	}
	printf("redis connect sucess ip: %s  port: %d\n", REDIS_HOST, REDIS_PORT);

	/*test为key， hello为vlaue*/
	char *cmd1 = "set test hello";
	r = (redisReply*)redisCommand(c, cmd1);
	if (NULL == r) {
		printf("Redis Command error [%s]\n", cmd1);
		redisFree(c);  
		return;
	}   
	if (r->type == REDIS_REPLY_ERROR ) { 
		printf("Redis Command[%s], error:%s\n", cmd1, r->str);
		freeReplyObject(r);
		redisFree(c);  
		return;
	}  
	printf("redis command execute success[%s]\n", cmd1);
	freeReplyObject(r);//释放redisCommand返回值replsy所占用的内存

	/*获取test的值*/
	char *cmd2 = "get testno";
	r = (redisReply*)redisCommand(c, cmd2);
	if (NULL == r) {
		printf("Redis Command error [%s]\n", cmd2);
		redisFree(c);  
		return;
	}   
	if (r->type == REDIS_REPLY_ERROR ) { 
		printf("Redis Command[%s], error:%s\n", cmd2, r->str);
		freeReplyObject(r);
		redisFree(c);  
		return;
	}  
	printf("get test value is: %s\n", r->str);
	freeReplyObject(r);

	const char* cmd3 = "strlen test";  
	r = (redisReply*)redisCommand(c, cmd3);  
	if ( r->type != REDIS_REPLY_INTEGER)  
	{  
		printf("Failed to execute command[%s]\n", cmd3);  
		freeReplyObject(r);  
		redisFree(c);  
		return;  
	}
	printf("The length of 'test' is %lld.\n", r->integer);       
	freeReplyObject(r); 

	/*释放数据库连接*/ 
	redisFree(c);  
	return;
}

int main()
{
	redis_cli();

	return 0;
}
