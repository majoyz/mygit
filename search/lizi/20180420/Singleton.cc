#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
template <typename T>
class TemplateSingleton
{
public:
    template <typename... Args>
    static T * getInstance(Args...);
    static void destory();
    template <typename... Args>
    static void getInit(Args...);
    static void mydelete();
private:
    TemplateSingleton();
    virtual ~TemplateSingleton();
   
    static T * _pinstance;
    static pthread_once_t _once;
};
template <typename T>
T * TemplateSingleton<T>::_pinstance;

template <typename T>
pthread_once_t TemplateSingleton<T>::_once=PTHREAD_ONCE_INIT;

template <typename T>
template <typename... Args>
T* TemplateSingleton<T>::getInstance(Args... args)
{
    getInit(args...);     
    return _pinstance;
}

template <typename T>
TemplateSingleton<T>::~TemplateSingleton()
{}

template <typename T>
template <typename... Args>
void TemplateSingleton<T>::getInit(Args... args)
{
    if(_pinstance==NULL)
        _pinstance=new T(args...);
    pthread_once(&_once,destory);
}

template <typename T>
void TemplateSingleton<T>::mydelete()
{
    if(_pinstance)
        delete _pinstance;
}

template <typename T>
void TemplateSingleton<T>::destory()
{
   atexit(mydelete); 
}
int main(void)
{
    string *p1=TemplateSingleton<string>::getInstance("hello");
    string *p2=TemplateSingleton<string>::getInstance("hello");
    printf("%p\n",p1);
    printf("%p\n",p2);
    return 0;
}
