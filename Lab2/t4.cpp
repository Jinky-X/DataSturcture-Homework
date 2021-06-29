#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXSIZE = 1000;

template<class T>
class List
{
    T data[MAXSIZE];
    int len;
public:
    List()
    {
        len = 0;
    }

    List(int n)
    {
        len = n;
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
        }
        clean();
    }

    void add(T tgt)
    {
        if (len < MAXSIZE)
            data[len++] = tgt;
        else throw "add: Overflow";
    }

    void clean()
    {
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                if (data[i] == data[j] && i != j)
                {
                    remove(j + 1);
                    j--;
                }
    }

    void remove(int index)
    {
        if (index > len || index < 0) throw "remove: invalid index";
        for (int i = index - 1; i < len; i++)
            data[i] = data[i + 1];
        len--;
    }

    void display()
    {
    	if (!len)
		{
			cout << "NULL" << endl;
			return;
		} 
        for (int i = 0; i < len; ++i)
        {
            cout << data[i] << endl;
        }
    }

    template<class T1>
    friend List<T1> list_intersection(List<T1> &a, List<T1> &b);

    template<class T2>
    friend List<T2> list_U(List<T2> &a, List<T2> &b);

    template<class T3>
    friend List<T3> list_complement(List<T3> &a, List<T3> &b);
};

template<class T>
List<T> list_intersection(List<T> &a, List<T> &b)
{
    List<T> out;
    T temp;
    for (int i = 0; i < a.len; ++i)
        for (int j = 0; j < b.len; ++j)
            if (a.data[i] == b.data[j])
                out.add(a.data[i]);
    out.clean();
    return out;
}

template<class T>
List<T> list_U(List<T> &a, List<T> &b)
{
    List<T> out;
    for (int i = 0; i < a.len; ++i)
        out.add(a.data[i]);
    for (int i = 0; i < b.len; ++i)
        out.add(b.data[i]);
    out.clean();
    return out;
}

template<class T>
List<T> list_complement(List<T> &a, List<T> &b) // a-b
{
    List<T> out;
    bool is;
    for (int i = 0; i < a.len; ++i)
    {
        is = 1;
        for (int j = 0; j < b.len; ++j)
            if (a.data[i] == b.data[j])
            {
                is = 0;
                break;
            }
        if (is)
            out.add(a.data[i]);
    }
    return out;
}

int main()
{
    int len1 = -1, len2 = -1;
    while (len1 < 0)
    {
        cout << "please enter length of a:";
        cin >> len1;
        if (len1 < 0)
            cout << "Invalid length!" << endl;
    }
    while (len2 < 0)
    {
        cout << "please enter length of b:";
        cin >> len2;
        if (len2 < 0)
            cout << "Invalid length!" << endl;
    }
    cout << "Please input data of a:";
    List<int> test1(len1);
    cout << "Please input data of b:";
    List<int> test2(len2);
    cout << "Done!\n";
    cout << "a ¡É b:\n";
    list_intersection(test1, test2).display();
    cout << "\na ¡È b:\n";
    list_U(test1, test2).display();
    cout << "\na-b:\n";
    list_complement(test1, test2).display();
    return 0;
}
