#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAXSIZE = 100;

template<class T>
class seqStack
{
    T data[MAXSIZE];
    int top;
public:
    seqStack()
    {
        top = -1;
    }

    ~seqStack()
    {}

    void push(T tgt)
    {
        if (top < MAXSIZE - 1)
            data[++top] = tgt;
        else throw "overflow";
    }

    T pop()
    {
        if (top != -1)
            return data[top--];
        else throw "underflow";
    }

    T peek()
    { return data[top]; }

    int isEmpty()
    {
        if (top == -1)
            return 1;
        else return 0;
    }

    void display()
    {
        if (!top)
        {
            cout << "NULL";
            return;
        }
        for (int i = 0; i < top + 1; i++)
            cout << data[i] << " ";
    }
};

template<class T>
class cirQueue
{
    T data[MAXSIZE];
    int front, rear;
public:
    cirQueue()
    {
        front = rear = 0;
    }

    ~cirQueue()
    {}

    T DeQueue()
    {
        if (front == rear)
            throw "underflow";
        else
        {
            front = (front + 1) % MAXSIZE;
            return data[front];
        }
    }

    void EnQueue(T tgt)
    {
        if ((rear + 1) % MAXSIZE == front)
            throw "overflow";
        rear = (rear + 1) % MAXSIZE;
        data[rear] = tgt;
    }

    T isEmpty()
    {
        if (front == rear)
            return 1;
        return 0;
    }

    T peekRear()
    {
        if (this->isEmpty())
            throw "empty";
        return data[rear];
    }

    T peekTop()
    {
        if (this->isEmpty())
            throw "empty";
        return data[(front + 1) % MAXSIZE];
    }

    void display()
    {
        if (this->isEmpty())
        {
            cout << "NULL";
            return;
        }
        for (int i = front + 1; i <= rear; i = (i + 1) % MAXSIZE)
            cout << data[i] << " ";
    }
};

template<class T>
void stackReceive(seqStack<T> &tgt)
{
    cirQueue<T> temp;
    while (!tgt.isEmpty())
        temp.EnQueue(tgt.pop());
    while (!temp.isEmpty())
        tgt.push(temp.DeQueue());
}

int main()
{
    int len, t;
    seqStack<int> test;
    cout << "input length:";
    cin >> len;
    cout << "input data:";
    for (int i = 0; i < len; ++i)
    {
        cin >> t;
        test.push(t);
    }
    stackReceive(test);
    test.display();
    return 0;
}
