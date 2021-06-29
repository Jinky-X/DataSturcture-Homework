#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

const int Maxsize = 1000000;
struct node
{
    int data;
    node *next;
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

    void add_random(int a[], int n)
    {
        node *p = first->next, *temp;
        while (p)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
        first->next = NULL;
        node *pNode;
        for (int i = 0; i < n; ++i)
        {
            pNode = new node;
            pNode->data = a[i];
            add_node(first, pNode);
        }
    }

    void add()
    {
        int tgt;
        node *pNode, *p, *prev = first;
        pNode = new node;
        cin >> tgt;
        pNode->data = tgt;
        p = first->next;
        if (!p)
        {
            add_node(first, pNode);
            return;
        }
        while (p->next && p->data < tgt)
        {
            p = p->next;
            prev = prev->next;
        }
        if (p->data >= tgt)
            add_node(prev, pNode);
        else add_node(p, pNode);

    }

    void add(int tgt)
    {
        node *pNode, *p, *prev = first;
        pNode = new node;
        pNode->data = tgt;
        p = first->next;
        if (!p)
        {
            add_node(first, pNode);
            return;
        }
        while (p->next && p->data < tgt)
        {
            p = p->next;
            prev = prev->next;
        }
        if (p->data >= tgt)
            add_node(prev, pNode);
        else add_node(p, pNode);

    }

    void delete_node(int index) //todo
    {
        node *p = first->next, *temp;
        if (index <= 0) throw "delete_node: Invalid index!";
        index -= 2;
        while (p->next && index) //tgt is p->next
        {
            p = p->next;
            index--;
        }
        if (!index)
        {
            temp = p->next;
            p->next = temp->next;
            delete temp;

        } else throw "delete_node: Invalid index!";
    }

    void swap(node *tgt) //swap tgt+1 and tgt+2
    {
        node *temp2 = tgt->next->next, *temp1 = tgt->next;
        tgt->next = temp2;
        temp1->next = temp2->next;
        temp2->next = temp1;
    }

    void add_node(node *prev0, node *tgt)
    {
        node *temp;
        temp = prev0->next;
        prev0->next = tgt;
        tgt->next = temp;
    }

    void ListSort()
    {
        node *p = first->next, *prev = first, *temp;
        int done = 0;
        if (!p) return;
        while (!done)
        {
            done = 1;
            while (p->next)
            {
                if (p->data > p->next->data)
                {
                    swap(prev);
                    done = 0;
                    prev = prev->next;
                } else
                {
                    prev = p;
                    p = p->next;
                }
            }
            p = first->next;
            prev = first;
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

    void reverse()
    {
        node *p = first->next, *temp1 = first->next->next, *temp2;
        bool isLast = false;
        while (!isLast)
        {
            temp2 = temp1->next;
            temp1->next = p;
            p = temp1;
            temp1 = temp2;
            if (!temp2) isLast = true;
        }
        first->next->next = NULL;
        first->next = p;
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
        if (!p)
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

    void change(int index, int value)
    {
        delete_node(index);
        add(value);
    }

};

void controller()
{
    default_random_engine random(time(NULL));
    uniform_int_distribution<int> dist(0, Maxsize);
    int fun = 1, len = -1, temp, temp1, *a, isRandom = 0;
    char *s;
    while (len < 0)
    {
        cout << "please enter length:";
        cin >> len;
        if (len < 0)
            cout << "Invalid length!" << endl;
    }
    cout << "please input data:";
    Linklist test(len);
    system("cls");
    while (fun)
    {
        cout
                << "please select a function:\n1.insert\n2.delete\n3.change\n4.get number\n"
                   "5.find index\n6.display\n7.get length\n8.reverse\n9.fill by random numbers\n0.exit\nPlease enter a code:";
        cin >> fun;
        switch (fun)
        {
            case 1:
                cout << "please enter a number:";
                cin >> temp;
                try
                {
                    test.add(temp);
                    cout << "Done!" << endl;
                }
                catch (char const *s)
                { cout << s << endl; }
                break;
            case 2:
                cout << "please enter an index:";
                cin >> temp;
                try
                {
                    test.delete_node(temp);
                    cout << "Done!" << endl;
                }
                catch (char const *s)
                { cout << s << endl; }
                break;
            case 3:
                cout << "please enter an index:";
                cin >> temp;
                cout << "please enter a number:";
                cin >> temp1;
                try
                {
                    test.change(temp, temp1);
                    cout << "Done!" << endl;
                }
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
                if (isRandom)
                {
                    cout << "Sorry, display function has been disabled\n";
                    break;
                }
                cout << "the list is:\n";
                test.display();
                break;
            case 7:
                cout << "the length is ";
                cout << test.get_length() << endl;
                break;
            case 8:
                test.reverse();
                cout << "Done!" << endl;
                break;
            case 9:
                a = new int[Maxsize];
                for (int i = 0; i < Maxsize; ++i)
                    a[i] = dist(random);
                test.add_random(a, Maxsize);
                isRandom = 1;
                cout << "Done!" << endl;
                break;
            case 0 :
                return;
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
