#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

int main()
{
    const int len = 1000000;
    long double sum = 0;
    srand((unsigned) time(NULL)); // make a seed of rand()
    int *tgt = new int[len];
    for (int i = 0; i < len; i++)
        tgt[i] = 0;
    for (int i = 0; i < len; i++)
        tgt[i] = int(rand() * 10000 / 32767); //max of rand() is 32767
    sort(tgt, tgt + len);
    for (int i = 0; i < len; i++)
        sum += tgt[i];
    cout << "Min: " << tgt[1] << "\nMax: " << tgt[len - 1] << "\nMean: " << sum / len << "\nmid: " << tgt[len / 2]
         << endl;
    system("pause");
    return 0;
}
