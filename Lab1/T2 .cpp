#include<iostream>
#include<cmath>

using namespace std;

class time
{
private:
    int year, mon, day, isPrime;
public:
    time(int y, int m, int d)
    {
        year = y;
        mon = m;
        day = d;
        isPrimeJud();
    }

    time()
    {

        cout << "Year:";
        cin >> year;
        cout << "Month:";
        cin >> mon;
        cout << "Day:";
        cin >> day;
        while (mon>12 || mon < 1 || day<1 || day>monDayJud())
        {
            cout << "Invalid input!\nYear:";
            cin >> year;
            cout << "Month:";
            cin >> mon;
            cout << "Day:";
            cin >> day;
        }
        isPrimeJud();
    }

    void isPrimeJud()
    {
        if (year % 4 == 0 && year % 100 != 0) isPrime = 1;
        else if (year % 400 == 0) isPrime = 1;
        else isPrime = 0;
    }

    void display() const
    {
        cout << year << "-" << mon << "-" << day << endl;
    }

    int monDayJud() const
    {
        if (mon == 12)
            return 31;
        if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10)
            return 31;
        if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            return 30;
        if (mon == 2)
            return 28 + isPrime;
    }


    friend time plus0(time &a, int b);


    friend int operator-(time a, time b);


    friend int comp(time a, time b);


    friend bool operator==(time a, time b);
};

int comp(time a, time b)
{
    if (a == b) return 2;
    else if (a.year != b.year) return (a.year > b.year);
    else if (a.mon != b.mon) return (a.mon > b.mon);
    else return (a.day > b.day);
} // 2-> a=b , 1-> a>b , 0-> a<b


time plus0(time &a, int b)
{
    a.year += (b / 146097) * 400;
    b = b % 146097;
    if (b == 0) return a;
    else
    {
        if (a.mon == 12)
            if (a.day == a.monDayJud())
            {
                a.mon = 1;
                a.year++;
                a.day = 1;
                a.isPrimeJud();
            } else a.day++;
        else if (a.day == a.monDayJud())
        {
            a.mon++;
            a.day = 1;
        } else a.day++;
        return plus0(a, b - 1);
    }
}
int operator-(time a, time b)
{
    int tgt = 0;
    if (comp(a, b) == 2) return 0;
    if (comp(a, b))
        while (!(a == b))
        {
            b = plus0(b, 1);
            tgt++;
        }
    else return -(b - a);
    return tgt;
}

bool operator==(time a, time b)
{
    if (a.mon == b.mon && a.day == b.day && a.year == b.year) return true;
    else return false;
}

int main()
{
    cout << "The first date:\n";
    time a;
    cout << "\nThe second date:\n";
    time b;
    cout << "The two dates are " << abs(a-b) << " days apart."<<endl;
    system("pause");
    return 0;
}
