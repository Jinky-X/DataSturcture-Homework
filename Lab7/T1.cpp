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
public:
    Graph(const string &filename)
    {
        ifstream in(filename);
        if (!in.is_open())
            throw invalid_argument("File can not be found");
        in >> iVertex;
        if (iVertex > MaxSize)
            throw invalid_argument("Overflow");
        for (int i = 0; i < iVertex; ++i)
            in >> vertex[i];
        for (int i = 0; i < iVertex; ++i)
            for (int j = 0; j < iVertex; ++j)
                in >> arc[i][j];
        in.close();
    }

    void DFSTraverse(int i = 0)
    {
        static bool visited[MaxSize] = {false};
        cout << vertex[i] << " ";
        visited[i] = true;
        for (int j = 0; j < iVertex; ++j)
            if (arc[i][j] && arc[i][j] != -1 && !visited[j])
                DFSTraverse(j);
    }

    void BFSTraverse(int i = 1)
    {
        if (i > iVertex || i < 1)
            throw invalid_argument("BFS:Invalid index");
        i--;
        if (!iVertex) return;
        int *que = new int[iVertex], front = 1, rear = 0, curr;
        bool *visited = new bool[iVertex];
        for (int j = 0; j < iVertex; ++j)
            visited[j] = false;
        que[1] = i;
        cout << vertex[i] << " ";
        visited[i] = true;
        while (front != rear)
        {
            curr = que[++rear];
            for (int j = 0; j < iVertex; ++j)
                if (arc[curr][j] && arc[curr][j] != -1 && !visited[j])
                {
                    cout << vertex[j] << " ";
                    visited[j] = true;
                    que[++front] = j;
                }
        }
    }

    void find(T tgt)
    {
        int loc, count;
        for (loc = 0; loc < iVertex; ++loc)
            if (vertex[loc] == tgt)
                break;
        if (loc == iVertex)
            throw invalid_argument("Target do not exist");
        cout << "\nIn:\n";
        count = 0;
        for (int i = 0; i < iVertex; ++i)
            if (arc[i][loc] && arc[i][loc] != -1)
            {
                cout << setw(6) << vertex[i] << " -> " << vertex[loc] << " : " << arc[i][loc] << endl;
                count++;
            }
        cout << "In degree is: " << count << endl;
        count = 0;
        cout << "\nOut:\n";
        for (int i = 0; i < iVertex; ++i)
            if (arc[loc][i] && arc[loc][i] != -1)
            {
                cout << setw(6) << vertex[loc] << " -> " << vertex[i] << " : " << arc[loc][i] << endl;
                count++;
            }
        cout << "Out degree is: " << count << endl;
    }
};

int main()
{
    Graph<string> g("Lab7_data1.txt");
    int fun, temp;
    string str;
    while (true)
    {
        system("cls");
        cout << "Please select a function:\n1.DFSTraverse\n2.BFSTraverse\n3.find\n0.exit" << endl;
        cin >> fun;
        switch (fun)
        {
            case 0:
                return 233;
            case 1:
                cout << "Please enter beginning point:(Number)" << endl;
                cin >> temp;
                try
                {
                    g.DFSTraverse(temp - 1);
                }
                catch (invalid_argument &err)
                {
                    cerr << err.what();
                }
                break;
            case 2:
                cout << "Please enter beginning point:(Number)" << endl;
                cin >> temp;
                try
                {
                    g.BFSTraverse(temp);
                }
                catch (invalid_argument &err)
                {
                    cerr << err.what();
                }
                break;
            case 3:
                cout << "Please enter target:" << endl;
                cin >> str;
                try
                {
                    g.find(str);
                }
                catch (invalid_argument &err)
                {
                    cerr << err.what();
                }
                break;
            default:
                cout << "Invalid command!";
        }
        cout << "\n";
        system("pause");
    }
}
