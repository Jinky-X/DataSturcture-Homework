#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <iomanip>

#pragma GCC optimize(2)
using namespace std;

const int MaxSize = 10000;
struct node
{
    long long data;
    node *next, *prev;
};

class Linklist
{
    node *first, *last;
    int length = 0;

    static void add_node(node *prev0, node *tgt)
    {
        node *temp;
        temp = prev0->next;
        prev0->next = tgt;
        tgt->prev = prev0;
        if (temp)
            temp->prev = tgt;
        tgt->next = temp;
    }

    static void delete_node(node *tgt)
    {
        if (!tgt) throw invalid_argument("tgt is empty");
        tgt->prev->next = tgt->next;
        if (tgt->next)
            tgt->next->prev = tgt->prev;
        delete tgt;
    }

public:
    void push_back(long long tgt)
    {
        node *pNode;
        pNode = new node;
        pNode->data = tgt;
        add_node(last, pNode);
        last = last->next;
        length++;
    }

    long long operator[](int index)
    {
        node *p = first->next;
        index++;
        if (index <= 0) throw invalid_argument("find_num: Invalid index!");
        index--;
        while (p->next && index)
        {
            p = p->next;
            index--;
        }
        if (!index)
        {
            return p->data;
        } else throw invalid_argument("find_num: Invalid index!");
    }

    int size()
    {
        return length;
    }

    void display(ostream &out, int len)
    {
        int count = 0;
        node *p = first->next;
        if (!p)
        {
            out << "NULL" << endl;
            return;
        }
        while (p && count < len)
        {
            out << setprecision(10) << p->data << endl;
            p = p->next;
            count++;
        }
    }

    Linklist()
    {
        first = new node;
        first->next = nullptr;
        last = first;
    }

    ~Linklist()
    {
        node *p = first->next, *temp;
        while (p)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
        delete first;
    }

    Linklist(const Linklist &ori)
    {
        first = new node;
        first->next = nullptr;
        last = first;
        length = ori.length;
        for (node *p = ori.first->next; p; p = p->next)
            push_back(p->data);
    }

    void delete_duplicate()
    {
        for (node *p = first->next; p; p = p->next)
            for (node *q = p->next; q; q = q->next)
                if (q->data == p->data)
                {
                    q = q->prev;
                    delete_node(q->next);
                }
    }
};

int main()
{
    Linklist l;
    default_random_engine random(time(nullptr));
    uniform_int_distribution<long long> dist(0, (long long)(pow(10, 11) - 1));
    while (l.size() < MaxSize)
    {
        int len = MaxSize - l.size();
        for (int i = 0; i < len * 1.3; ++i)
        {
            l.push_back(dist(random));
        }
        l.delete_duplicate();
    }
    ofstream out("T1_result.txt");
    l.display(out, MaxSize);
    out.close();
    cout << "Done!\n";
    system("pause");
    return 0;
}
