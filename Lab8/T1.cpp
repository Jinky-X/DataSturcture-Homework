#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>

#pragma GCC optimize(2)
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

    int Dijkstra_finLow(const double dist[], const bool visited[]) //return -1 when dijkstra is done
    {
        int iLow = 0;
        double low = dist[0];
        for (int i = 1; i < iVertex; ++i)
        {
            if (dist[i] != -1 && !visited[i] && (low > dist[i] || visited[iLow]))
            {
                low = dist[i];
                iLow = i;
            }
        }
        if (!(dist[iLow] != -1 && !visited[iLow]))
            return -1;
        else return iLow;
    }

public:

    Graph()
    {
        iVertex = 0;
    }

    Graph(ifstream &in)
    {
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
            arc[iFrom][iTo] = len;
        }
    }

    void Dijkstra(T from)
    {
        double dist[iVertex];
        vector<T> path[iVertex];
        if (iVertex == 1) return;
        int iFrom = findIndex(from), iLow;
        bool visited[iVertex];
        for (int i = 0; i < iVertex; ++i)
            visited[i] = false;
        for (int i = 0; i < iVertex; ++i)
        {
            dist[i] = arc[iFrom][i];
            path[i].clear();
            if (arc[iFrom][i] != -1)
            {
                path[i].push_back(vertex[iFrom]);
                path[i].push_back(vertex[i]);
            }
        }
        visited[0] = true;
        for (iLow = Dijkstra_finLow(dist, visited); iLow != -1; iLow = Dijkstra_finLow(dist, visited))
        {
            visited[iLow] = true;
            for (int i = 0; i < iVertex; ++i)
                if (!visited[i] && arc[iLow][i] != -1 && dist[iLow] != -1 &&
                    (dist[i] == -1 || dist[i] > arc[iLow][i] + dist[iLow]))
                {
                    dist[i] = arc[iLow][i] + dist[iLow];
                    path[i] = path[iLow];
                    path[i].push_back(vertex[i]);
                }
        }
        cout << "\nResult:\n";
        for (int iTo = 0; iTo < iVertex; ++iTo)
        {
            if (dist[iTo] == -1)
            {
                cout << "Path: " << vertex[iFrom] << " -> " << vertex[iTo] << " do not exist!\n";
            } else
            {
                for (int i = 0; i < path[iTo].size() - 1; ++i)
                    cout << path[iTo][i] << " -> ";
                cout << path[iTo][path[iTo].size() - 1] << " : " << dist[iTo] << "\n";
            }
        }
    }

    void Floyd()
    {
        vector<double> dist[iVertex];
        vector<vector<T>> path[iVertex];
        T from, to;
        int iFrom, iTo;
        char flag;
        for (int i = 0; i < iVertex; ++i)
        {
            for (int j = 0; j < iVertex; ++j)
            {
                dist[i].push_back(arc[i][j]);
                vector<T> temp;
                path[i].push_back(temp);
                if (arc[i][j] != -1)
                {
                    path[i][j].push_back(vertex[i]);
                    path[i][j].push_back(vertex[j]);
                }
            }
        }
        for (int k = 0; k < iVertex; ++k)
            for (int i = 0; i < iVertex; ++i)
                for (int j = 0; j < iVertex; ++j)
                    if (dist[i][k] != -1 && dist[k][j] != -1 &&
                        (dist[i][j] == -1 || dist[i][k] + dist[k][j] < dist[i][j]))
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = path[i][k];
                        path[i][j].pop_back();
                        path[i][j].insert(path[i][j].end(), path[k][j].begin(), path[k][j].end());
                    }
        while (true)
        {
            cout << "Please input the beginning and ending of path:" << endl;
            cin >> from >> to;
            iFrom = findIndex(from);
            iTo = findIndex(to);
            if (dist[iFrom][iTo] == -1)
            {
                cout << "Path: " << vertex[iFrom] << " -> " << vertex[iTo] << " do not exist!\n";
            } else
            {
                for (int i = 0; i < path[iFrom][iTo].size() - 1; ++i)
                    cout << path[iFrom][iTo][i] << " -> ";
                cout << path[iFrom][iTo][path[iFrom][iTo].size() - 1] << " : " << dist[iFrom][iTo] << "\n";
            }
            cout << "end?(Y/N):" << endl;
            cin >> flag;
            if (flag == 'y' || flag == 'Y')
                return;
        }
    }
};

int main()
{
    ifstream fin("Lab8_data1.txt");
    if (!fin.is_open())
    {
        cout << "file not found";
        system("pause");
        return -1;
    }
    Graph<string> g(fin);
    string str, tgt;
    int fun;
    while (true)
    {
        system("cls");
        cout << "Please select a function:\n1.Dijkstra\n2.Floyd\n0.exit\n";
        cin >> fun;
        switch (fun)
        {
            case 0:
                return 233;
            case 1:
                cout << "Please enter beginning point:" << endl;
                cin >> tgt;
                g.Dijkstra(tgt);
                break;
            case 2:
                g.Floyd();
                break;
            default:
                cout << "Invalid command!";
        }
        cout << "\n";
        system("pause");
    }
}
