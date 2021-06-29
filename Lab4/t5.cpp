#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include<cstring>
#include<fstream>

using namespace std;

bool check(string tgt)
{
    string temp;
    int len;
    int index[27] = {1, 25417, 43830, 75937, 94670, 108867, 120760, 131713, 145456, 159798, 162638, 166590,
                     176592, 196397, 209855, 222536, 257396, 259189, 275972, 314736, 333555, 356322, 361651,
                     368210, 145456, 368717, 370104};
    ifstream in(R"(words_alpha.txt)");
    if (!in.is_open())
    {
        cout << "未成功打开文件" << endl;
    }
    for (int i = 0; i < tgt.length(); ++i)
    {
        if (tgt[i] >= 'A' && tgt[i] <= 'Z')
            tgt[i] += 32;
    }
    for (int i = 0; i < index[int(tgt[0]) - 97]; ++i)
        getline(in, temp);

    if (tgt[0] == 'x')
        len = 507;
    else if (tgt[0] == 'y')
        len = 14342;
    else len = index[tgt[0] - 96] - index[int(tgt[0]) - 97];
    for (int i = 0; i < len; i++)
    {
        getline(in, temp);
        if (tgt == temp)
        {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

int main()
{
    char a[100][100], temp[100];
    string tgt;
    int c = 0,l, i, j;
    cout << "please input the order of the matrix:" << endl;
    cin >> l;
    cout << "please input the matrix:\n";
    for (i = 0; i < l; i++)
        for (j = 0; j < l; j++)
        {
            a[i][j] = getchar();
            while (a[i][j] == '\n')
                a[i][j] = getchar();
        }
    cout << "\nThe matrix includes words:\n" ;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < l; j++)
            temp[j] = a[i][j];
        temp[j] = '\0';
        tgt = temp;
        if (check(tgt))
            cout << ++c << ": " << tgt << endl;
    }
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < l; j++)
            temp[j] = a[j][i];
        temp[j] = '\0';
        tgt = temp;
        if (check(tgt))
            cout << ++c << ": " << tgt << endl;
    }
    for (j = 0; j < l; j++)
        temp[j] = a[j][j];
    temp[j] = '\0';
    tgt = temp;
    if (check(tgt))
        cout << ++c << ": " << tgt << endl;
    for (j = 0; j < l; j++)
        temp[j] = a[j][l - j];
    temp[j] = '\0';
    tgt = temp;
    if (check(tgt))
        cout << ++c << ": " << tgt << endl;
    if(!c)
    	cout << "NONE";
    return 0;
}
