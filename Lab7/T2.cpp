#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept> 

using namespace std;
const int MaxSize = 100;

template<class T>
class Graph
{
    T vertex[MaxSize];
    int iVertex;
    double arc[MaxSize][MaxSize];

    int findIndex(T tgt)
    {
        for (int i = 0; i < iVertex; ++i)
        {
            if (tgt == vertex[i])
                return i;
        }
        throw invalid_argument("Target can not be found");
    }

    struct primNode
    {
        int from;
        double lowCost;
        bool isIn = false;
    };

    int findLowPrim(primNode *edge)
    {
        int out = -1, min;
        for (int i = 0; i < iVertex; ++i)
        {
            if (!edge[i].isIn && edge[i].lowCost != -1 && (out == -1 || min > edge[i].lowCost))
            {
                min = edge[i].lowCost;
                out = i;
            }
        }
        return out;
    }

    bool isPrimDone(primNode *edge)
    {
        for (int i = 0; i < iVertex; ++i)
        {
            if (!edge[i].isIn && edge[i].lowCost != -1 && edge[i].lowCost != 0)
                return false;
        }
        return true;
    }

    struct edgeData
    {
        int from, to;
        double weight;

        static bool compareEdge(const edgeData &a, const edgeData &b)
        {
            return a.weight < b.weight;
        }
    };

    int findRoot(int i, int *parent)
    {
        if (i == parent[i]) return i;
        return findRoot(parent[i], parent);
    }

public:
    Graph(const string &filename)
    {
        ifstream in(filename);
        T from, to;
        int iFrom, iTo;
        double len;
        if (!in.is_open())
            throw invalid_argument("File can not be found");
        in >> iVertex;
        if (iVertex > MaxSize)
            throw invalid_argument("Overflow");
        for (int i = 0; i < iVertex; ++i)
            in >> vertex[i];
        for (int i = 0; i < iVertex; ++i)
            for (int j = 0; j < iVertex; ++j)
                arc[i][j] = -1;
        for (int i = 0; i < iVertex; ++i)
        {
            arc[i][i] = 0;
        }
        while (!in.eof())
        {
            in >> from >> to >> len;
            iFrom = findIndex(from);
            iTo = findIndex(to);
            arc[iFrom][iTo] = arc[iTo][iFrom] = len;
        }
        in.close();
    }

    void Prim()
    {
        primNode shortEdge[iVertex];
        int low;
        double length = 0;
        for (int i = 1; i < iVertex; ++i)
        {
            shortEdge[i].lowCost = arc[0][i];
            shortEdge[i].from = 0;
        }
        shortEdge[0].isIn = true;
        while (!isPrimDone(shortEdge))
        {
            low = findLowPrim(shortEdge);
            cout << vertex[shortEdge[low].from] << "<-->" << vertex[low] << " : " << shortEdge[low].lowCost << "km"
                 << "\n";
            length += shortEdge[low].lowCost;
            shortEdge[low].isIn = true;
            for (int i = 0; i < iVertex; ++i)
                if (!shortEdge[i].isIn &&
                    (shortEdge[i].lowCost == -1 || (arc[low][i] != -1 && shortEdge[i].lowCost > arc[low][i])))
                {
                    shortEdge[i].from = low;
                    shortEdge[i].lowCost = arc[low][i];

                }
        }
        cout << "Total: " << length << "km" << endl;
    }

    void Kruskal()
    {
        int parent[iVertex], count = 0, iEdge = 0, numEdge = 0;
        double length = 0;
        edgeData edge[MaxSize];
        for (int i = 0; i < iVertex; ++i)
        {
            parent[i] = i;
            for (int j = 0; j < iVertex; ++j)
            {
                if (arc[i][j] && arc[i][j] != -1)
                {
                    edge[numEdge].weight = arc[i][j];
                    edge[numEdge].from = i;
                    edge[numEdge].to = j;
                    numEdge++;
                }
            }
        }
        sort(edge, edge + numEdge, edgeData::compareEdge);
        while (count < iVertex && iEdge < numEdge)
        {
            int r1 = findRoot(parent[edge[iEdge].from], parent), r2 = findRoot(parent[edge[iEdge].to], parent);
            if (r1 != r2)
            {
                parent[r1] = r2;
                cout << vertex[edge[iEdge].from] << "<-->" << vertex[edge[iEdge].to] << " : " << edge[iEdge].weight
                     << "km" << "\n";
                count++;
                length += edge[iEdge].weight;
            }
            iEdge++;
        }
        cout << "Total: " << length << "km" << endl;
    }
};

int main()
{
    Graph<string> g("Lab7_data2.txt");
    int fun;
    string str;
    while (true)
    {
        system("cls");
        cout << "Please select a function:\n1.Prim\n2.Kruskal\n0.exit" << endl;
        cin >> fun;
        switch (fun)
        {
            case 0:
                return 233;
            case 1:
                g.Prim();
                break;
            case 2:
                g.Kruskal();
                break;
            default:
                cout << "Invalid command!";
        }
        cout << "\n";
        system("pause");
    }
}
