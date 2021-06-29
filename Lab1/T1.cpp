#include <iostream> 
#include <math.h>
#include <algorithm>
using namespace std;
int gcd(int a, int b)
{
	if (a < b) 
	{
		int temp = a;
		a = b;
		b = temp;
	} ; //make sure a>b
	int c = a % b;
	if ( c==0 ) return b ;
	else return gcd(c , b);
}
int main()
{
	int a,b;
	cout << "Please input 2 numbers: ";
	cin >> a >> b ;
	if (a>0 && b>0 ) 
	{
		cout << "GCD(standard): " << gcd(a,b) << endl;
		cout << "GCD(algorithm.h): " << __gcd(a,b) << endl;
		cout << "LCM: " << a * b/ __gcd(a,b) << endl;	
	}
	
	else cout << "Invalid Input" << endl;
	system("pause");
	return 0;
} 
