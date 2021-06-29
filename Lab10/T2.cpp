#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include <iomanip>

using namespace std;
const int MAXSIZE = 150000;

template<typename T>
void insert_sort(T data[], int length)
{
    int j;
    T temp;
    for (int i = 1; i < length; ++i)
    {
        temp = data[i];
        for (j = i - 1; j >= 0 && data[j] > temp; --j)
            data[j + 1] = data[j];
        data[j + 1] = temp;
    }
}

template<typename T>
void shell_sort(T data[], int length)
{
    int j;
    T temp;
    for (int d = length / 2; d > 0; d = d / 2)
    {
        for (int i = d; i < length; ++i)
        {
            temp = data[i];
            for (j = i - d; j >= 0 && data[j] > temp; j -= d)
                data[j + d] = data[j];
            data[j + d] = temp;
        }
    }
}

template<typename T>
void pop_sort(T data[], int length)
{
    T temp;
    int last;
    while (length > 1)
    {
        last = -1;
        for (int i = 0; i < length - 1; ++i)
        {
            if (data[i] > data[i + 1])
            {
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                last = i;
            }
        }
        length = last + 1;
    }
}

template<typename T>
void quick_sort(T data[], const int length)
{
    if (length <= 1) return;
    int i = 0, j = length - 1;
    T temp;
    while (i < j)
    {
        for (; data[j] > data[i]; j--)
        {}
        if (i == j) break;
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
        for (; data[j] >= data[i] && i != j; i++)
        {}
        if (i == j) break;
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    quick_sort(data, i);
    quick_sort(data + i + 1, length - i - 1);
}

template<typename T>
void select_sort(T data[], const int length)
{
    int iMin;
    T temp;
    for (int i = 0; i < length; ++i)
    {
        iMin = i;
        for (int j = i + 1; j < length; ++j)
            if (data[j] < data[iMin])
                iMin = j;
        if (iMin != i)
        {
            temp = data[i];
            data[i] = data[iMin];
            data[iMin] = temp;
        }
    }
}

template<typename T>
void heap_sort(T data[], const int length)
{
    int end = length;
    T temp;
    auto sift = [=, &end](int index) -> void  // using lambda expression
    {
        T temp;
        int i = index, j = 2 * i + 1;
        while (j < end - 1)
        {
            if (data[j] < data[j + 1] && j + 1 < end - 1)
                j++;
            if (data[i] > data[j])
                break;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i = j;
            j = 2 * i + 1;
        }
    };
    for (int i = length / 2 - 1; i >= 0; --i)
        sift(i);
    for (; end > 0; end--)
    {
        temp = data[0];
        data[0] = data[end - 1];
        data[end - 1] = temp;
        sift(0);
    }
}

template<typename T>
void merge(T in[], T out[], int front, int mid, int end)
{
    int i = front, j = mid, k = front;
    while (i < mid && j < end)
    {
        if (in[i] < in[j])
            out[k++] = in[i++];
        else
        {
            out[k++] = in[j];
            j++;
        }
    }
    if (i < mid)
        while (i < mid)
            out[k++] = in[i++];
    else
        while (j < end)
            out[k++] = in[j++];
}

template<typename T>
void merge_pass(T in[], T out[], int length, int step)
{
    int i = 0;
    while (i <= length - 2 * step)
    {
        merge(in, out, i, i + step, i + 2 * step);
        i += 2 * step;
    }
    if (i < length - step)
        merge(in, out, i, i + step, length);
    else
        for (int j = i; j < length; ++j)
            out[j] = in[j];
}

template<typename T>
void merge_sort(T data[], const int length)
{
    T temp[length];
    int step = 1;
    while (step < length)
    {
        merge_pass(data, temp, length, step);
        step *= 2;
        merge_pass(temp, data, length, step);
        step *= 2;
    }
}

int main()
{
    ifstream fin("Lab10_data.txt");
    ofstream out("T2_result.csv");
    if (!fin.is_open())
    {
        cout << "file not found!\n";
        return -1;
    }
    int *result[7], ori[MAXSIZE];
    clock_t startTime[7], endTime[7];
    for (int i = 0; i < 7; ++i)
    {
        result[i] = new int[MAXSIZE];
    }
    for (int i = 0; i < MAXSIZE; ++i)
    {
        fin >> ori[i];
        for (int j = 0; j < 7; ++j)
            result[j][i] = ori[i];
    }

    void
    (*sort_func[7])(int [], int) ={insert_sort, shell_sort, pop_sort, quick_sort, select_sort, heap_sort, merge_sort};
    for (int i = 0; i < 7; ++i)
    {
        startTime[i] = clock();
        sort_func[i](result[i], MAXSIZE);
        endTime[i] = clock();
    }
    string name[] = {"insert_sort", "shell_sort", "pop_sort", "quick_sort", "select_sort", "heap_sort",
                     "merge_sort"};
    out << "original data,insert_sort,shell_sort,pop_sort,quick_sort,select_sort,heap_sort,merge_sort\n";
    for (int i = 0; i < MAXSIZE; ++i)
    {
        out << ori[i] << ",";
        for (int j = 0; j < 6; ++j)
        {
            out << result[j][i] << ",";
        }
        out << result[6][i] << "\n";
    }
    cout << setw(13) << "Function " <<"|  Time used \n-------------------------\n";
    for (int i = 0; i < 7; ++i)
    {
        cout << setw(13) << name[i] << "| " << endTime[i] - startTime[i] << "ms\n";
    }
    fin.close();
    out.close();
    cout << "Done!\n";
    system("pause");
    return 0;
}
