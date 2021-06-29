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
    int from, to, weight, ee, el;
    Edge *next;
};

struct Vertex
{
    int key, inDegree = 0, outDegree = 0, ve = 0, vl = 999999;
    Edge *first;
    vector<Edge> back;
};

class AOEGraph
{
    Vertex vtx[MaxSize];
    int length;

    int findIndex(int tgt)
    {
        for (int i = 0; i < length; ++i)
        {
            if (vtx[i].key == tgt)
                return i;
        }
        return -1;
    }

public:
    AOEGraph(ifstream &in)
    {
        in >> length;
        string sKey;
        Edge *temp;
        int from;
        for (int i = 0; i < length; ++i)
        {
            vtx[i].first = nullptr;
            vtx[i].key = i;  //can be changed when necessary
        }
        for (int i = 0; !in.eof(); ++i)
        {
            in >> from;
            temp = new Edge;
            temp->from = --from;
            in >> temp->to;
            temp->to--;
            in >> temp->weight;
            temp->next = vtx[from].first;
            vtx[from].first = temp;
            vtx[temp->to].inDegree++;
            vtx[from].outDegree++;
            vtx[temp->to].back.push_back(*temp);
        }
    }

    void TopoSort()
    {
        int curr;
        vector<Edge> resultEdge, inData[length];
        vector<int> resultVertex;
        queue<int> que;
        int inTemp[length], outTemp[length];
        Edge *p;
        for (int i = 0; i < length; i++)
        {
            inTemp[i] = vtx[i].inDegree;
            outTemp[i] = vtx[i].outDegree;
            inData[i] = vtx[i].back;
            if (!vtx[i].inDegree)
                que.push(i);
        }
        while (!que.empty())
        {
            curr = que.front();
            que.pop();
            for (p = vtx[curr].first; p; p = p->next)
            {
                if (vtx[p->to].ve < vtx[curr].ve + p->weight)
                {
                    vtx[p->to].ve = vtx[curr].ve + p->weight;
                }
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
        que.push(curr);  //curr point to the final vertex
        vtx[curr].vl = vtx[curr].ve;
        while (!que.empty())
        {
            curr = que.front();
            que.pop();
            for (int i = 0; i < inData[curr].size(); ++i)
            {
                if (vtx[inData[curr][i].from].vl > vtx[curr].vl - inData[curr][i].weight)
                {
                    vtx[inData[curr][i].from].vl = vtx[curr].vl - inData[curr][i].weight;
                }
                outTemp[inData[curr][i].from]--;
                if (!inTemp[inData[curr][i].from])
                {
                    que.push(inData[curr][i].from);
                }
            }
        }
        for (int i = 0; i < length; ++i)
        {
            if (vtx[i].ve == vtx[i].vl) resultVertex.push_back(i + 1);
            for (p = vtx[i].first; p; p = p->next)
            {
                p->ee = vtx[i].ve;
                p->el = vtx[p->to].vl - p->weight;
                if (p->ee == p->el)
                    resultEdge.push_back(*p);
            }
        }
        sort(resultEdge.begin(), resultEdge.end(), Compare);
        cout << "Key activities: \n";
        for (int i = 0; i < resultVertex.size(); ++i)
        {
            cout << resultVertex[i] << " ";
        }
        cout << "\nKey route: \n";
        for (auto it = resultEdge.begin(); it != resultEdge.end(); it++)
        {
            cout << it->from + 1 << " -> " << it->to + 1 << "\n";
        }
    }

    static bool Compare(Edge &e1, Edge &e2)
    {
        if (e1.to < e2.from || e1.from < e2.from)
            return true;
        return false;
    }

};

int main()
{
    ifstream fin("Lab8_data3.txt");
    if (!fin.is_open())
    {
        cout << "file not found";
        system("pause");
        return -1;
    }
    AOEGraph g(fin);
    g.TopoSort();
    system("pause");

}
