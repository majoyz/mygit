//......
//......连接池

#include "MutexLock.h"
#include <hiredis/hiredis.h>
#include <time.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <memory>

using std::queue;
using std::string;
using std::shared_ptr;

namespace wd
{

inline string int2str(int number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

class RedisClient  
{  
public:  
    RedisClient(const string & ip, unsigned short port, int timeout = 2000);  
	~RedisClient();
  
    bool executeCommand(const char *cmd, size_t len, string &response);  
    redisReply* executeCommand(const char *cmd, size_t len);  
  
private:
    redisContext* CreateContext();  
    void ReleaseContext(redisContext *ctx, bool active);  
    bool CheckStatus(redisContext *ctx);  
private:  
    int _timeout;
    unsigned short _port;  
    string _ip;  
    MutexLock _mutex;
    queue<redisContext *> m_clients;  
    time_t _beginInvalidTime;  
    static const int _maxReconnectInterval = 3;  
};  
  
RedisClient::RedisClient(string ip, unsigned short port, int timeout)  
: _timeout(timeout)
, _port(port)
, _ip(ip)
{
  
    _beginInvalidTime = 0;  
}  
  
RedisClient::~RedisClient()  
{  
    MutexLockGuard mlg(_mutex);  
    while(!m_clients.empty())  
    {  
        redisContext *ctx = m_clients.front();  
        redisFree(ctx);  
        m_clients.pop();  
    }  
}  
  
bool RedisClient::executeCommand(const char *cmd, size_t len, string &response)  
{  
    redisReply *reply = executeCommand(cmd, len);  
    if(reply == NULL) return false;  
  
    std::shared_ptr<redisReply> autoFree(reply, freeReplyObject);  
    if(reply->type == REDIS_REPLY_INTEGER)  
    {  
        response = int2str(reply->integer);  
        return true;  
    }  
    else if(reply->type == REDIS_REPLY_STRING)  
    {  
        response.assign(const_cast<const char*>(reply->str), reply->len); 
        return true;  
    }  
    else if(reply->type == REDIS_REPLY_STATUS)  
    {  
        response.assign(const_cast<const char *>(reply->str), reply->len);  
        return true;  
    }  
    else if(reply->type == REDIS_REPLY_NIL)  
    {  
        //response = "";  
        return true;  
    }  
    else if(reply->type == REDIS_REPLY_ERROR)  
    {  
        response.assign(reply->str, reply->len);  
        return false;  
    }  
    else if(reply->type == REDIS_REPLY_ARRAY)  
    {  
        //response = string("Not Support Array Result!!!");  
        return false;  
    }  
    else  
    {  
        //response = "Undefine Reply Type";  
        return false;  
    }  
}  
  
redisReply* RedisClient::executeCommand(const char *cmd, size_t len)  
{  
    redisContext *ctx = CreateContext();  
    if(ctx == NULL) return NULL;  
  
    redisReply *reply = (redisReply*)redisCommand(ctx, "%b", cmd, len);  
  
    ReleaseContext(ctx, reply != NULL);  
  
    return reply;  
}  
  
redisContext* RedisClient::CreateContext()  
{  
    {  
        MutexLockGuard autolock(_mutex);  
        if(!m_clients.empty())  
        {  
            redisContext *ctx = m_clients.front();  
            m_clients.pop();  
  
            return ctx;  
        }  
    }  
  
    time_t now = time(NULL); 
    if(now < _beginInvalidTime + _maxReconnectInterval) return NULL;  
  
    struct timeval tv;  
    tv.tv_sec = _timeout / 1000;  
    tv.tv_usec = (_timeout % 1000) * 1000;;  
    redisContext *ctx = redisConnectWithTimeout(_ip.c_str(), _port, tv);  
    if(ctx == NULL || ctx->err != 0)  
    { 
        if(ctx != NULL) redisFree(ctx);  
        _beginInvalidTime = time(NULL);  
        return NULL;  
    }  
  
    return ctx;  
}  
  
void RedisClient::ReleaseContext(redisContext *ctx, bool active)  
{  
    if(ctx == NULL) return;  
    if(!active) {redisFree(ctx); return;}  
  
    MutexLockGuard auotlock(_mutex);  
    m_clients.push(ctx);  
}  
  
bool RedisClient::CheckStatus(redisContext *ctx)  
{  
    redisReply *reply = (redisReply*)redisCommand(ctx, "ping");  
    if(reply == NULL) return false;  
  
    std::shared_ptr<redisReply> autoFree(reply, freeReplyObject);  
  
    if(reply->type != REDIS_REPLY_STATUS) return false;  
    if(strcmp(reply->str,"PONG") != 0) return false;  
  
    return true;  
}  
}//end of namespace wd
