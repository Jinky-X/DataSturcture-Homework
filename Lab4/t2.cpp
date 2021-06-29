#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int maxsize = 100;
int a[maxsize][maxsize];

bool check(int l)
{
    int i, sum, sum0 = 0, b[l * l + 1];
    for (int j = 1; j <= l * l; ++j)
        b[j] = 0;
    for (i = 0; i < l; i++)
        for (int j = 0; j < l; j++)
            b[a[i][j]]++;
    for (int j = 1; j <= l * l; ++j)
        if (b[j] == 0) return false;
    for (int j = 0; j < l; j++)
    {
        sum0 += a[0][j];
    }
    for (i = 1; i < l; i++)
    {
        sum = 0;
        for (int j = 0; j < l; j++)
            sum += a[i][j];
        if (sum != sum0) return false;
    }
    for (i = 0; i < l; i++)
    {
        sum = 0;
        for (int j = 0; j < l; j++)
            sum += a[j][i];
        if (sum != sum0) return false;
    }
    for (i = 0, sum = 0; i < l; i++)
        sum += a[i][i];
    if (sum != sum0) return false;
    for (i = 0, sum = 0; i < l; i++)
        sum += a[i][l - i - 1];
    if (sum != sum0) return false;
    return true;
}

void magic(int l)
{
    int i, j, c = 1;
    for (i = 0; i < l; ++i)
        for (j = 0; j < l; ++j)
            a[i][j] = 0;
    if (!l % 2)
        cout << "Invalid size\n";
    i = l / 2;
    j = 0;
    a[j][i] = 1;
    while (c != l * l)
    {
        i = (i + l - 1) % l;
        j = (j + l - 1) % l;
        if (a[j][i])
        {
            j = (j + 2) % l;
            i = (i + 1) % l;
        }
        a[j][i] = ++c;
    }

}

int main()
{
    while (1)
    {
        int fun, l, loc;
        system("cls");
        cout << "please select a function:\n1.check a matrix\n2.initialize a magic matrix\n0.exit" << endl;
        cin >> fun;
        switch (fun)
        {
            case 0:
                return 0;
            case 1:
                cout << "please enter the length of the matrix:";
                cin >> l;
                cout << "please enter the matrix:\n";
                for (int i = 0; i < l; ++i)
                    for (int j = 0; j < l; ++j)
                        cin >> a[i][j];

                if (check(l)) cout << "It is a magic matrix." << endl;
                else cout << "It is not a magic matrix." << endl;
                break;
            case 2:
                cout << "Please enter the length of the magic matrix:";
                cin >> l;
                magic(l);
                cout << "The result is:\n";
                for (int i = 0; i < l; ++i)
                {
                    for (int j = 0; j < l; ++j)
                        cout << setw(4) <<a[i][j] ;
                    cout << "\n";
                }
                break;
            default:
                cout << "Invalid command!";
        }
        system("pause");
    }
    return 0;
}
