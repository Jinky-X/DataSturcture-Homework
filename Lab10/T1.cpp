#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

const int MAXSIZE = 11, empty_signal = 2147483647, modLen = 11;

class closed_hash_table
{
    int data[MAXSIZE], mode, TSL = 0, amount = 0; //mode=1 liner mode=2 square , TSL=totally search length

    int Hash(int d)
    {
        return d % modLen;
    }

    int get_fail_TSL()
    {
        int i, count = 0;
        int tgt = empty_signal;
        if (mode == 1)
        {
            for (int j = 0; j < modLen; ++j)
            {
                for (i = j; data[i] != empty_signal; i = (i + 1) % MAXSIZE)
                    count++;
            }
        } else
        {
            int index, move = 1;
            for (int j = 0; j < modLen; ++j)
            {
                for (index = j; data[index] != empty_signal && abs(move) < MAXSIZE;)
                {
                    count++;
                    index = (index + move) % MAXSIZE;
                    if (move > 0)
                        move = -move;
                    else
                        move = pow(sqrt(-move) + 1, 2);
                }
            }
        }
        return count + modLen;
    }

public:
    closed_hash_table()
    {
        for (int i = 0; i < MAXSIZE; ++i)
        {
            data[i] = empty_signal;
        }
    }

    closed_hash_table(int in[], int len, int scanMode)  //scanMode=1 liner scanMode=2 square
    {
        int temp;
        if (len > MAXSIZE)
            throw invalid_argument("closed_hash_table overflow!");
        mode = scanMode;
        amount = len;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            data[i] = empty_signal;
        }
        if (scanMode == 1)
        {
            for (int i = 0; i < len; ++i)
            {
                if (in[i] == empty_signal)
                {
                    throw invalid_argument("number overflow");
                }
                for (temp = Hash(in[i]); data[temp] != empty_signal; temp = (temp + 1) % MAXSIZE)
                { TSL++; }
                data[temp] = in[i];
                TSL++;
            }
        } else if (scanMode == 2)
        {
            int move; //true -> to find in front
            for (int i = 0; i < len; ++i)
            {
                if (in[i] == empty_signal)
                {
                    throw invalid_argument("number overflow");
                }
                move = 1;
                int index;
                for (temp = index = Hash(in[i]); data[index] != empty_signal && abs(move) < MAXSIZE;)
                {
                    TSL++;
                    index = (temp + move) % MAXSIZE;
                    if (move > 0)
                        move = -move;
                    else
                        move = pow(sqrt(-move) + 1, 2);
                }
                data[index] = in[i];
                TSL++;
            }
        } else throw invalid_argument("invalid mode");
    }

    bool search(int tgt)
    {
        int i;
        if (tgt == empty_signal)
        {
            throw invalid_argument("number overflow");
        }
        if (mode == 1)
        {
            for (i = Hash(tgt); data[i] != empty_signal; i = (i + 1) % MAXSIZE)
            {
                if (data[i] == tgt)
                    return true;
            }
        } else
        {
            int index, move = 1;
            for (i = index = Hash(tgt); data[index] != empty_signal && abs(move) < MAXSIZE;)
            {
                if (data[i] == tgt)
                    return true;
                i = (index + move) % MAXSIZE;
                if (move > 0)
                    move = -move;
                else
                    move = pow(sqrt(-move) + 1, 2);
            }
            if (data[index] == tgt) return true;
        }
        return false;
    }

    int get_ASL_success()
    {
        return TSL / amount;
    }

    void display_ASL()
    {
        cout << "搜索成功的ASL为 " << setprecision(3) << double(TSL) / amount << "  搜索失败的ASL为 "
             << double(get_fail_TSL()) / modLen << "\n";
    }
};

class opened_hash_table
{
    struct node
    {
        int data;
        node *next = nullptr;
    };

    int TSL = 0, amount;
    node data[modLen];

    int Hash(int d)
    {
        return d % modLen;
    }

public:
    opened_hash_table()
    {}

    opened_hash_table(int in[], int len)
    {
        node *p, *temp;
        amount = len;
        for (int i = 0; i < len; ++i)
        {
            for (p = data + Hash(in[i]); p->next; p = p->next)
            { TSL++; }
            temp = new node;
            temp->data = in[i];
            temp->next = p->next;
            p->next = temp;
            TSL++;
        }
    }

    bool search(int tgt)
    {
        node *p;
        for (p = (data + Hash(tgt))->next; p; p = p->next)
        {
            if (p->data == tgt)
                return true;
        }
        return false;
    }

    void display_ASL() const
    {
        cout << "搜索成功的ASL为 " << setprecision(3) << double(TSL) / amount << "  搜索失败的ASL为 "
             << (TSL) / double(modLen) << "\n";
    }
};

int main()
{
    int input[] = {47, 7, 29, 11, 16, 92, 22, 8, 3}, temp;
    closed_hash_table l1(input, 9, 1);
    closed_hash_table l2(input, 9, 2);
    opened_hash_table l3(input, 9);
    cout << "闭散列表使用线性探测法：\n";
    l1.display_ASL();
    cout << "\n闭散列表使用平方探测法：\n";
    l2.display_ASL();
    cout << "\n开散列表使用拉链法：\n";
    l3.display_ASL();
    cout << "\n\n";
    cout << "请输入需要搜索的数：\n";
    cin >> temp;
    if (l1.search(temp)) cout << "闭散列表使用线性探测法：该数存在\n";
    else cout << "闭散列表使用线性探测法：该数不存在\n";
    if (l2.search(temp)) cout << "闭散列表使用平方探测法：该数存在\n";
    else cout << "闭散列表使用平方探测法：该数不存在\n";
    if (l3.search(temp)) cout << "开散列表使用拉链法：该数存在\n";
    else cout << "开散列表使用拉链法：该数不存在\n";
    system("pause");
    return 0;
}
