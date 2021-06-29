#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXSIZE = 100;

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

int main()
{
    int iTrain, iBuffer, temp, count = 0, tgt, outSuccess, buffSuccess;
    cout << "please enter the amount of trains:";
    cin >> iTrain;
    cout << "please enter the amount of buffer tracks:";
    cin >> iBuffer;
    cout << "please input number of trains:";
    cirQueue<int> qTrain[iBuffer + 1], qOut;
    for (int i = 0; i < iTrain; ++i)
    {
        cin >> temp;
        qTrain[0].EnQueue(temp);
    }
    while (count != iTrain)
    {
        outSuccess = 0;
        buffSuccess = 0;
        tgt = (qOut.isEmpty()) ? 1 : (qOut.peekRear() + 1);
        for (int i = 0; i < iBuffer + 1; ++i)
            if (!qTrain[i].isEmpty() && qTrain[i].peekTop() == tgt)
            {
                outSuccess = 1;
                qOut.EnQueue(qTrain[i].DeQueue());
                count++;
                if (i)
                    cout << "train " << tgt << " : buffer " << i << " -> out" << endl;
                else cout << "train " << tgt << " : origin -> out" << endl;
                break;
            }
        if (!outSuccess)
        {
            if (qTrain[0].isEmpty())
                break;
            tgt = qTrain[0].peekTop();
            for (int i = 1; i < iBuffer + 1; ++i)
                if (qTrain[i].isEmpty() || tgt > qTrain[i].peekRear())
                {
                    buffSuccess = 1;
                    qTrain[i].EnQueue(qTrain[0].DeQueue());
                    cout << "train " << tgt << " : origin -> buffer " << i << "\n";
                    break;
                }
            if (!buffSuccess)
                break;
        }
    }
    if (count == iTrain)
    {
        cout << "done!" << endl;
    } else
        cout << "failed!" << endl;
    return 0;
}     
