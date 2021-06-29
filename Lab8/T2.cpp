#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>

#pragma GCC optimize(2)
using namespace std;
const int MaxSize = 100;

struct Edge
{
    int to;
    Edge *next;
};

struct Vertex
{
    string key, data;
    int inDegree = 0;
    Edge *first;
};

class AOVGraph
{
    Vertex vtx[MaxSize];
    int length;

    int findIndex(const string &tgt)
    {
        for (int i = 0; i < length; ++i)
        {
            if (vtx[i].key == tgt)
                return i;
        }
        return -1;
    }

public:
    AOVGraph(ifstream &in)
    {
        in >> length;
        string sKey;
        Edge *temp;
        int iKey;
        for (int i = 0; i < length; ++i)
        {
            vtx[i].first = nullptr;
            in >> vtx[i].key;
        }
        for (int i = 0; i < length; ++i)
        {
            in >> vtx[i].key >> vtx[i].data;
            for (in >> sKey; sKey != "#"; in >> sKey)
            {
                iKey = findIndex(sKey);
                temp = new Edge;
                temp->to = i;
                temp->next = vtx[iKey].first;
                vtx[iKey].first = temp;
                vtx[i].inDegree++;
            }
        }
    }

    void TopoSort()
    {
        int temp;
        vector<string> result;
        queue<int> que;
        int inTemp[length];
        Edge *p;
        for (int i = 0; i < length; i++)
        {
            inTemp[i] = vtx[i].inDegree;
            if (!vtx[i].inDegree)
            {
                que.push(i);
            }
        }
        while (!que.empty())
        {
            temp = que.front();
            que.pop();
            result.push_back(vtx[temp].data);
            for (p = vtx[temp].first; p; p = p->next)
            {

                inTemp[p->to]--;
                if (!inTemp[p->to])
                {
                    que.push(p->to);
                }
            }
        }
        for (int i = 0; i < length; i++)
            if (inTemp[i])
            {
                cerr << "ERR:circle exist!\n";
                return;
            }
        cout << "Result:\n";
        for (auto &i : result)
        {
            cout << i << "\n";
        }
        cout << "\n";
    }


};

int main()
{
    ifstream fin("Lab8_data2.txt");
    if (!fin.is_open())
    {
        cout << "file not found";
        system("pause");
        return -1;
    }
    AOVGraph g(fin);
    g.TopoSort();
    system("pause");

}
