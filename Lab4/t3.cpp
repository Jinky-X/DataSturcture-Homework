#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

bool KMatcher(const char a[], const char b[], int ia, int ib, int k)
{
    int i = 0, j = 0, c = 0;
    while (i <= ia && j <= ib && c <= k)
    {
        if (i == ia)
        {
            c += ib - j;
            break;
        }
        if (j == ib)
        {
            c += ia - i;
            break;
        }
        if (a[i] == b[j])
        {
            i++;
            j++;
        } else
        {
            c++;
            if (i == ia - 1)
            {
                if (a[i] == b[j + 1]) c--;
                c += ib - j - 1;
                break;
            }
            if (j == ib - 1)
            {
                if (b[i] == a[j + 1]) c--;
                c += ia - i - 1;
                break;
            }
            if (a[i] == b[j + 1])
            {
                i++;
                j += 2;
            } else if (a[i + 1] == b[j])
            {
                i += 2;
                j++;
            } else
            {
                i++;
                j++;
            }
        }

    }
    if (c <= k) return true;
    return false;
}

int main()
{
    char a[100], b[100];
    int i, j, k;
    cout << "Please enter the first string:" << endl;
    cin >> a;
    cout << "Please enter the second string:" << endl;
    cin >> b;
    cout << "Please enter K:" << endl;
    cin >> k;
    for (i = 0; a[i] != '\0'; ++i)
    {}
    for (j = 0; b[j] != '\0'; ++j)
    {}
    if (KMatcher(a, b, i, j, k))
        cout << "The answer is true!" << endl;
    else cout << "The answer is false!" << endl;
    return 0;
}
