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

int read()
{
    char t;
    while (true)
    {
        t = getchar();
        if (48 <= t && t <= 57)
            return int(t) - 48;
        switch (t)
        {
            case '+' :
                return 11;
            case '-' :
                return 12;
            case '*' :
                return 13;
            case '/' :
                return 14;
            case '(' :
                return 15;
            case ')' :
                return 16;
            case '#' :
                return 17;
            default :
                continue;
        }
    }
}

int isSenior(int a, int b) //1:a>b 0:a=b -1:a<b
{
    int inStackPrior[7] = {3, 3, 5, 5, 1, 6, 0}, outStackPrior[7] = {2, 2, 4, 4, 6, 1, 0};
    if (inStackPrior[a - 11] > outStackPrior[b - 11])
        return 1;
    else if (inStackPrior[a - 11] < outStackPrior[b - 11])
        return -1;
    else
        return 0;
}

int calculate(int a, int b, int s)
{
    switch (s)
    {
        case 11:
            return a + b;
        case 12:
            return a - b;
        case 13:
            return a * b;
        case 14:
            return a / b;
        default:
            throw "ERR";
    }
}

int main()
{
    seqStack<int> OPD, OPS;
    int corr, isNum = 0, prev;
    cout << "目前已实现：\n字符间无需打空格\n括号前后可以省略乘号\n带正负号时不需要打括号\n判断语法错误\n";
    cout << "Please input an expression:(end by #)\n#";
    OPS.push(17);
    corr = read();
    try
    {
        while (!OPS.isEmpty())
        {
            if (0 <= corr && corr <= 9)
            {
                if (isNum == 2)  //case of '(...)2'
                {
                    prev = 13;
                    OPS.push(13);
                }
                if (prev == 19) //case of a*-b
                    corr = -corr;
                if (isNum == 1)  //read number > 9
                    OPD.push(OPD.pop() * 10 + corr);
                else
                    OPD.push(corr);
                if (!isNum && prev != 19)
                    prev = corr;
                corr = read();
                isNum = 1;
            } else
            {
                if (isNum && corr == 15) // cases of a(...)
                    OPS.push(13);
                if ((prev > 10 && prev < 15) && (corr > 10 && corr < 13))
                {
                    prev = corr + 7;
                    corr = read();
                    continue;
                    //throw "invalid";
                }
                switch (isSenior(OPS.peek(), corr))
                {
                    case 0:
                        OPS.pop();
                        isNum = 2;
                        if (!OPS.isEmpty())
                        {
                            prev = corr;
                            corr = read();
                        }
                        break;
                    case -1:
                        OPS.push(corr);
                        {
                            prev = corr;
                            corr = read();
                        }
                        isNum = 0;
                        break;
                    case 1:
                        OPD.push(calculate(OPD.pop(), OPD.pop(), OPS.pop()));
                        isNum = 0;
                        continue;
                }
            }
        }
        cout << "The answer is:" << OPD.pop();
    }
    catch (const char *p)
    {
        cout << "Invalid expression!";
    }
    return 0;
}
