#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include<stdexcept>
#include<iomanip>

using namespace std;
const int MAX = 100;

template<class T>
struct node
{
    T data;
    int row, column;
    node *rNext, *cNext;
};

template<class T>
class Matrix
{
    node<T> firstRow[MAX], firstColumns[MAX];
    int rows{}, columns{};

    node<T> *getPrevRow(int r, int c)
    {
        node<T> *p = firstRow + r;
        while (p->rNext != firstRow + r && p->rNext->column < c + 1)
            p = p->rNext;
        return p;
    }

    node<T> *getPrevColumn(int r, int c)
    {
        node<T> *p = firstColumns + c;
        while (p->cNext != firstColumns + c && p->cNext->row < r + 1)
            p = p->cNext;
        return p;
    }

public:
    Matrix(int r, int c)
    {
        rows = r;
        columns = c;
        for (int i = 0; i < r; ++i)
        {
            firstRow[i].rNext = firstRow + i;
            firstRow[i].column = -1;
        }
        for (int i = 0; i < c; ++i)
        {
            firstColumns[i].cNext = firstColumns + i;
            firstColumns[i].row = -1;
        }
    }

    void add(T d, int r, int c)
    {
        node<T> *p, *temp, *q;
        p = getPrevRow(r, c);
        q = getPrevColumn(r, c);
        if (p->rNext->column == c + 1)
        {
            p->rNext->data += d;
            return;
        }
        temp = new node<T>;
        temp->data = d;
        temp->row = r + 1;
        temp->column = c + 1;
        temp->rNext = p->rNext;
        temp->cNext = q->cNext;
        p->rNext = temp;
        q->cNext = temp;
    }

    Matrix()
    {
        int d, r = 0, c;
        cout << "Please enter rows and columns:" << endl;
        cin >> rows >> columns;
        for (int i = 0; i < rows; ++i)
        {
            firstRow[i].rNext = firstRow + i;
            firstRow[i].column = -1;
        }
        for (int i = 0; i < columns; ++i)
        {
            firstColumns[i].cNext = firstColumns + i;
            firstColumns[i].row = -1;
        }
        cout << "Please enter row, column and data:(end by -1 in row)\n";
        while (true)
        {
            cin >> r >> c >> d;
            if (r == -1) break;
            if (r > rows || c > columns || r <= 0 || c <= 0)
            {
                cout << "Invalid location, other data:" << endl;
            } else
                add(d, r - 1, c - 1);
        }
    }

    template<class T1>
    friend Matrix<T1> operator+(const Matrix<T1> &, const Matrix<T1> &);

    template<class T1>
    friend Matrix<T1> operator*(const Matrix<T1> &, const Matrix<T1> &);

    template<class T1>
    friend ostream &operator<<(ostream &, const Matrix<T1> &);

};


template<class T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
{

    if (a.rows != b.rows || a.columns != b.columns)
        throw invalid_argument("Plus Error: Two matrix are in different size");
    Matrix<T> out(a.rows, b.columns);
    for (int i = 0; i < a.rows; ++i)
        for (node<T> *p = a.firstRow[i].rNext; p != a.firstRow + i; p = p->rNext)
            out.add(p->data, p->row - 1, p->column - 1);
    for (int i = 0; i < b.rows; ++i)
        for (node<T> *p = b.firstRow[i].rNext; p != b.firstRow + i; p = p->rNext)
            out.add(p->data, p->row - 1, p->column - 1);
    return out;
}

template<class T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    T tData;
    node<T> *p1, *p2;
    if (a.columns != b.rows)
        throw invalid_argument("Invalid size for times");
    Matrix<T> out(a.rows, b.columns);
    for (int i = 0; i < a.rows; ++i)
        for (int j = 0; j < b.columns; ++j)
        {
            tData = 0;
            p1 = a.firstRow[i].rNext;
            p2 = b.firstColumns[j].cNext;
            while (p1 != a.firstRow + i && p2 != b.firstColumns + j)
                if (p1->column == p2->row)
                {
                    tData += p1->data * p2->data;
                    p1 = p1->rNext;
                    p2 = p2->cNext;
                } else if (p1->column > p2->row)
                    p2 = p2->cNext;
                else p1 = p1->rNext;
            out.add(tData, i, j);
        }
    return out;
}

template<class T>
ostream &operator<<(ostream &out, const Matrix<T> &tgt)
{
    node<T> *p;
    out << setiosflags(ios::left | ios::showpoint);
    out.precision(3);
    out << "-------------------\n";
    out << setw(5) << "row" << setw(8) << "column " << setw(6) << "data\n";
    out << "\b-------------------\n";
    for (int i = 0; i < tgt.rows; ++i)
    {
        p = tgt.firstRow[i].rNext;
        while (p != tgt.firstRow + i)
        {
            if (p->data)
                out << setw(5) << p->row << setw(8) << p->column << setw(6) << p->data << "\n";
            p = p->rNext;
        }
    }
    out << "-------------------\n";
    return out;
}

int main()
{
    cout << "Input Example: \n0 3 0\n0 0 0\n0 0 0\nInput:\n1 2 3\n-1 0 0\n\nPlease input a:" << endl;
    Matrix<int> test1;
    cout << "\nPlease input b:\n";
    Matrix<int> test2;
    try
    { cout << "\na + b = \n" << test1 + test2 << endl; }
    catch (invalid_argument &err)
    { cerr << err.what() << endl; }
    try
    { cout << "\na * b = \n" << test1 * test2 << endl; }
    catch (invalid_argument &err)
    { cerr << err.what() << endl; }
    return 0;
}

