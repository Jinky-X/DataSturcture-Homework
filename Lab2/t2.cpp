#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <exception>

using namespace std;

struct node
{
    int data;
    node *next, *prev;
};

class Linklist
{
    node *first;
public:
    void add()
    {
        int tgt;
        node *pNode, *p;
        pNode = new node;
        cin >> tgt;
        pNode->data = tgt;
        p = first->next;
        if (!p)
            add_node(first, pNode);
        else
        {
            while (p->next && p->data < tgt)
                p = p->next;
            if (p->data >= tgt)
                p = p->prev;
            add_node(p, pNode);
        }
    }

    void add(int tgt)
    {
        node *pNode, *p;
        pNode = new node;
        pNode->data = tgt;
        p = first->next;
        if (!p)
            add_node(first, pNode);
        else
        {
            while (p->next && p->data < tgt)
                p = p->next;
            if (p->data >= tgt)
                p = p->prev;
            add_node(p, pNode);
        }
    }

    void delete_node(int index)
    {
        node *p = first->next;
        if (index <= 0) throw "delete_node: Invalid index!";
        index--;
        while (p->next && index)
        {
            p = p->next;
            index--;
        }
        if (!index)
        {
            p->prev->next = p->next;
            if (p->next)
                p->next->prev = p->prev;
            delete p;
        } else throw "delete_node: Invalid index!";
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

    void ListSort()
    {
        node *p = first->next;
        int done = 0;
        if (!p) return;
        while (!done)
        {
            done = 1;
            while (p->next)
            {
                if (p->data > p->next->data)
                {
                    swap(p);
                    done = 0;
                }
            }
        }
    }

    int find_num(int index)
    {
        node *p = first->next;
        if (index <= 0) throw "find_num: Invalid index!";
        index--;
        while (p->next && index)
        {
            p = p->next;
            index--;
        }
        if (!index)
        {
            return p->data;
        } else throw "find_num: Invalid index!";
    }

    int get_length()
    {
        int i = 0;
        node *p = first->next;
        while (p)
        {
            p = p->next;
            i++;
        }
        return i;
    }

    Linklist find_index(int tgt)
    {
        int i = 1;
        Linklist out;
        node *p = first->next;
        while (p)
        {
            if (p->data == tgt)
                out.add(i);
            p = p->next;
            i++;
        }
        return out;
    }

    void display()
    {

        node *p = first->next;
        if(!p) 
		{
			cout << "NULL" << endl;
			return;
		}
        while (p)
        {
            cout << p->data << endl;
            p = p->next;
        }

    }

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

    void change(int index, int value)
    {
        delete_node(index);
        add(value);
    }
};

void controller()
{
    int fun = 1, len, temp, temp1;
    char *s;
    cout << "please enter length:";
    cin >> len;
    cout << "please input data:";
    Linklist test(len);
    system("cls");
    while (fun)
    {
        cout
                << "please select a function:\n1.insert\n2.delete\n3.change\n4.get number\n5.find index\n6.display\n7.get length\n0.exit\nPlease enter a code:";
        cin >> fun;
        switch (fun)
        {
            case 1:
                cout << "please enter a number:";
                cin >> temp;
                try
                { test.add(temp); }
                catch (char const *s)
                { cout << s << endl; }
                break;
            case 2:
                cout << "please enter an index:";
                cin >> temp;
                try
                { test.delete_node(temp); }
                catch (char const *s)
                { cout << s << endl; }
                break;
            case 3:
                cout << "please enter an index:";
                cin >> temp;
                cout << "please enter a number:";
                cin >> temp1;
                try
                { test.change(temp, temp1); }
                catch (char const *s)
                { cout << s << endl; }
                break;
            case 4:
                cout << "please enter an index:";
                cin >> temp;
                cout << "the number is:";
                try
                { cout << test.find_num(temp) << endl; }
                catch (char const *s)
                { cout << "\n" << s << endl; }
                break;
            case 5:
                cout << "please enter a number:";
                cin >> temp;
                cout << "the locations of the number are:\n";
                try
                { test.find_index(temp).display(); }
                catch (char const *s)
                { cout << s << endl; }
                break;
            case 6:
                cout << "the list is:\n";
                test.display();
                break;
            case 7:
                cout << "the length is ";
                cout << test.get_length() << endl;
                break;
            case 0:
                continue;
            default:
                cout << "Invalid input!" << endl;
        }
        system("pause");
        system("cls");
    }
}


int main()
{
    controller();
    return 0;
}
