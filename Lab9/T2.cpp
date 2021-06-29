#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdexcept>

using namespace std;

const int MaxSize = 10000;

class list
{
    int data[MaxSize], length;

    int search(int tgt, int begin, int end)
    {
        int index = (begin + end) / 2;
        cout << "comparing target " << tgt << " and data " << data[index] << ": ";
        if (data[index] == tgt)
        {
            cout << "Succeed\n";
            return index;
        }
        cout << "Failed\n";
        if (end - begin == 1)
            return -1;
        if (data[index] > tgt)
            return search(tgt, begin, index);
        return search(tgt, index, end);
    }

public:
    list()
    {
        length = 0;
    }

    void push_back(int in)
    {
        if (length == MaxSize)
            throw invalid_argument("overflow");
        data[length++] = in;
    }

    int search_recursion(int tgt)
    {
        if (!length)
            throw invalid_argument("empty");
        sort(data, data + length);
        search(tgt, 0, length);
    }

    int search(int tgt)
    {
        if (!length)
            throw invalid_argument("empty");
        sort(data, data + length);
        int begin = 0, end = length, index;
        while (true)
        {
            index = (begin + end) / 2;
            cout << "comparing target " << tgt << " and data " << data[index] << " :";
            if (data[index] == tgt)
            {
                cout << "Succeed\n";
                return index;
            }
            cout << "Failed\n";
            if (end - begin == -1)
                return -1;
            if (data[index] > tgt)
                end = index;
            else
                begin = index;
        }
    }


};

int main()
{
    ifstream fin("Lab9_data1.txt");
    if (!fin.is_open())
    {
        cout << "File not found\n";
        system("pause");
        return 2;
    }
    list l;
    int temp, result, tgt, way;
    for (int i = 0; i < 100; ++i)
    {
        fin >> temp;
        l.push_back(temp);
    }
    fin.close();
    cout << "Please enter the target:\n";
    cin >> tgt;
    cout << "Please select a way: \n1.recursion\n2.normal\n";
    cin >> way;
    if (way == 2)
        result = l.search(tgt);
    else if (way == 1)
        result = l.search_recursion(tgt);
    else
    {
        cout << "Invalid command\n";
        system("pause");
        return 1;
    }
    if (result != -1)
        cout << "The index (sorted) of target is: " << result + 1 << "\n";
    else
        cout << "Target do not exist\n";
    system("pause");
    return 0;
}
