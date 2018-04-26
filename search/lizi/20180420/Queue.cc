#include <iostream>
using namespace std;
template <typename T, int t = 10>
class Queue {
public:
    Queue();
    virtual ~Queue();
    bool empty();
    bool full();
    void push(const T data);
    T head();
    T tail();
    void pop();

private:
    T* p;
    int front;
    int back;
};
template <typename T, int t>
Queue<T, t>::Queue()
    : p(new T[t + 1]())
    , front(0)
    , back(0)
{
}

template <typename T, int t>
Queue<T, t>::~Queue()
{
    delete[] p;
}

template <typename T, int t>
bool Queue<T, t>::empty()
{
    return front == back;
}

template <typename T, int t>
bool Queue<T, t>::full()
{
    return front == (back + 1) % (t + 1);
}

template <typename T, int t>
void Queue<T, t>::push(const T data)
{
    if (!full()) {
        p[back] = data;
        ++back;
        back %= (t + 1);
    }
}

template <typename T, int t>
void Queue<T, t>::pop()
{
    if (!empty()) {
        ++front %= (t + 1);
    }
}

template <typename T, int t>
T Queue<T, t>::head()
{
    if (!empty()) {
        return p[front];
    }
}

template <typename T, int t>
T Queue<T, t>::tail()
{
    if (!empty()) {
        return p[(back + t) % (t + 1)];
    }
}

int main(void)
{
    Queue<int> q;
    int j;
    for (int i = 1; i != 20; i++) {
        q.push(i);
        cout << q.tail() << endl;
    }
    for (int i = 1; i != 20; i++) {
        if (q.empty())
            break;
        j = q.head();
        cout << j << endl;
        q.pop();
    }
    return 0;
}
