#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;
struct node
{
    int data1, data2;
    node *next, *prev;
};

class Linklist
{
    node *first;
public:
    Linklist(int n)
    {
        first = new node;
        first->next = NULL;
        for (int i = 0; i < n; i++)
            add();
    }

    Linklist()
    {
        first = new node;
        first->next = NULL;
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

    void add()
    {
        int tgt2, tgt1;
        node *pNode, *p;
        pNode = new node;
        cin >> tgt1;
        cin >> tgt2;
        pNode->data2 = tgt2;
        pNode->data1 = tgt1;
        p = first->next;
        if (!p)
            add_node(first, pNode);
        else
        {
            while (p->next && p->data2 < tgt2)
                p = p->next;
            if (p->data2 >= tgt2)
                p = p->prev;
            add_node(p, pNode);
        }
    }

    void add(node *a)
    {
        node *p;
        p = first->next;
        if (!p)
            add_node(first, a);
        else
        {
            while (p->next && p->data2 < a->data2)
                p = p->next;
            if (p->data2 == a->data2)
            {
                p->data1 = p->data1 + a->data1;
                if (!p->data1)
                {
                    p = p->prev;
                    delete p->next;
                    p->next = NULL;
                }
            } else
            {
                add_node(p, a);
            }
        }
    }

    void add(int tgt1, int tgt2)
    {
        node *pNode, *p;
        pNode = new node;
        pNode->data1 = tgt1;
        pNode->data2 = tgt2;
        p = first->next;
        if (!p)
            add_node(first, pNode);
        else
        {
            while (p->next && p->data2 < tgt2)
                p = p->next;
            if (p->data2 >= tgt2)
                p = p->prev;
            add_node(p, pNode);
        }
    }

    void swap(node *tgt) //swap tgt and tgt+1
    {
        node *temp = tgt->next;
        tgt->next = temp->next;
        temp->prev = tgt->prev;
        tgt->prev->next = temp;
        temp->next->prev = tgt;
    }

    void add_node(node *prev0, node *tgt)
    {
        node *temp;
        temp = prev0->next;
        prev0->next = tgt;
        tgt->prev = prev0;
        if (temp)
            temp->prev = tgt;
        tgt->next = temp;
    }

    void ListSort() //sort base on data2
    {
        node *p = first->next;
        int done = 0;
        if (!p) return;
        while (!done)
        {
            done = 1;
            while (p->next)
            {
                if (p->data2 > p->next->data2)
                {
                    swap(p);
                    done = 0;
                }
            }
        }
    }

    void display()
    {
        node *p = first->next;
        if (p == NULL)
        {
            cout << "0" << endl;
            return;
        }

        while (p->next)
        {
            if (p->data2 == 0)
                cout << p->data1 << " + ";
            else if (p->data2 < 0)
                cout << p->data1 << "x^(" << p->data2 << ") + ";
            else
                cout << p->data1 << "x^" << p->data2 << " + ";
            p = p->next;
        }
        cout << p->data1 << "x^" << p->data2 << "\n";
    }

    friend Linklist list_plus(Linklist &, Linklist &);

    friend Linklist list_times(Linklist &, Linklist &);
};

Linklist list_plus(Linklist &a, Linklist &b)
{
    Linklist out;
    node *p1 = a.first->next, *p2 = b.first->next, *pOut, *pNode, *pLow;

    while (p1 || p2)
    {

        if (!p1)
        {
            pLow = p2;
            p2 = p2->next;
        } else if (!p2 || p1->data2 < p2->data2)
        {
            pLow = p1;
            p1 = p1->next;
        } else
        {
            pLow = p2;
            p2 = p2->next;

        }
        if (!out.first->next)
        {
            out.first->next = new node;
            pOut = out.first->next;
            pOut->prev = out.first;
            pOut->data1 = pLow->data1;
            pOut->data2 = pLow->data2;
            pOut->next = NULL;
            continue;
        }
        if (pOut->data2 == pLow->data2)
        {
            pOut->data1 = pOut->data1 + pLow->data1;
            if (!pOut->data1)
            {
                pOut = pOut->prev;
                delete pOut->next;
                pOut->next = NULL;
            }
        } else
        {
            pNode = new node;
            pNode->data1 = pLow->data1;
            pNode->data2 = pLow->data2;
            out.add_node(pOut, pNode);
            pOut = pOut->next;
        }
    }
    return out;
}

Linklist list_times(Linklist &a, Linklist &b)
{
    Linklist out;
    node *p1 = a.first->next, *p2, *pOut, *pNode;

    while (p1)
    {
        p2 = b.first->next;
        while (p2)
        {
            pNode = new node;
            pNode->data1 = p1->data1 * p2->data1;
            pNode->data2 = p1->data2 + p2->data2;
            if (!out.first->next)
            {
                out.first->next = new node;
                pOut = out.first->next;
                pOut->prev = out.first;
                pOut->data1 = pNode->data1;
                pOut->data2 = pNode->data2;
                pOut->next = NULL;
                p2 = p2->next;
                continue;
            } else
                out.add(pNode);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return out;
}

int main()
{
    int len1 = -1, len2 = -1;
    while (len1 < 0)
    {
        cout << "please enter the length of a:";
        cin >> len1;
        if (len1 < 0) cout << "Invalid length!" << endl;
    }
    while (len2 < 0)
    {
        cout << "please enter the length of b:";
        cin >> len2;
        if (len2 < 0) cout << "Invalid length!" << endl;
    }
    cout << "Input example: x^2+3x^(-4) please input \"1 2 3 -4\"" << endl;
    cout << "Please input a: ";
    Linklist a(len1);
    cout << "Please input b: ";
    Linklist b(len2);
    cout << "a = ";
    a.display();
    cout << "b = ";
    b.display();
    cout << "a + b = ";
    list_plus(a, b).display();
    cout << "a * b = ";
    list_times(a, b).display();
    return 0;
}
