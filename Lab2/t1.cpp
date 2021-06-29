/* ÕÅ¾°Ðù 19336170 */
#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXSIZE = 1000;

class List
{
private:
    int a[MAXSIZE], len;

public:
    List()
    {
        len = 0;
    };

    List(int n)
    {
        if (n > MAXSIZE)
        {
            throw "Invalid size!";
        }
        len = n;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        sort(a, a + len);
    }

    List(int tgt[], int n)
    {
        if (n > MAXSIZE)
        {
            throw "Invalid size!";
        }
        len = n;
        for (int i = 0; i < n; ++i)
        {
            a[i] = tgt[i];
        }
    }

    ~List()
    {};

    void delete0(int tgt)
    {
        if (tgt <= 0 || tgt > len) throw "Invalid index!";
        if (len == 0) throw "Underflow!";
        for (int i = tgt - 1; i < len; i++)
            a[i] = a[i + 1];
        len--;
    }

    int find_num(int tgt)
    {
        if (tgt <= 0 || tgt > len)
            throw "Invalid location!";
        return a[tgt - 1];
    }

    List find_index(int tgt)
    {
        List out;
        for (int i = 0; i < len; i++)
        {
            if (a[i] == tgt)
                out.add(i+1);
        }
        return out;
    }

    void add(int tgt)
    {
        if (len == MAXSIZE) throw "Overflow!";
        a[len++] = tgt;
        sort(a, a + len);
    }

    int find_length()
    {
        return len;
    }

    int display()
    {
        if (len)
            for (int i = 0; i < len; ++i)
                cout << a[i] << endl;
        else cout << "NULL" << endl;
    }

    void change(int loc, int num)
    {
        if (loc > len || loc < 0)
        {
            throw "Invalid location!";
        }
        a[loc - 1] = num;
        sort(a, a + len);
    }
};

void controller()
{
    int fun = 1, len, temp, temp1;
    char *s;
    cout << "please enter length:";
    cin >> len;
    cout << "please input data:";
    List test(len);
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
                { test.delete0(temp); }
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
                cout << test.find_length() << endl;
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
