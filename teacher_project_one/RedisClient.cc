 ///
 /// @file    RedisClient.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-30 16:44:19
 ///
 
#include <hiredis/hiredis.h>
#include <string.h>

#include <iostream>
#include <string>
#include <memory>
using std::cout;
using std::endl;
using std::string;


class RedisClient
{
public:
	RedisClient(const string & ip, unsigned short port)
	: _ip(ip)
	, _port(port)
	, _ctx(NULL)
	, _reply(NULL)
	{
		connect();
	}

	~RedisClient()
	{
		if(_ctx)
		{
			redisFree(_ctx);
			_ctx = NULL;
		}
	}


	bool set(const string & key, const string & value)
	{
		_reply = (redisReply*)redisCommand(_ctx, "set %s %s", key.c_str(), value.c_str());
		std::shared_ptr<redisReply> autofree(_reply, freeReplyObject);
		switch(_reply->type)
		{
			case REDIS_REPLY_STATUS:
			{
				if(strstr(_reply->str, "OK"))
					return true;	
			}
			case REDIS_REPLY_ERROR:
				cout << _reply->str << endl;
				return false;
		}
		return false;
	}

	string get(const string & key)
	{
		_reply = (redisReply *)redisCommand(_ctx, "GET %s", key.c_str());
		std::shared_ptr<redisReply> autofree(_reply, freeReplyObject);
		if(_reply->type == REDIS_REPLY_STRING)
			return string(_reply->str);
		else 
			return string();
	}
	
private:
	bool connect()
	{
		_ctx = redisConnect(_ip.c_str(), _port);
		if(_ctx == NULL)
		{
			cout << "> redisConnect error " << endl;		
			return false;
		}
		else if(_ctx->err)
		{
			cout << "> Error: " << _ctx->errstr << "\n";		
			return false;
		}
		return true;
	}

private:
	string _ip;
	unsigned short _port;
	redisContext * _ctx;
	redisReply * _reply;
};
 
int main(void)
{
	RedisClient redisClient("127.0.0.1", 6379);
	cout << redisClient.get("hello") << endl;
	redisClient.set("hello", "world wa ha ha");
	cout << redisClient.get("hello") << endl;
	
	return 0;
}
