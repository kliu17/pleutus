#include <iostream>
using namespace std;

int main() {
	string a = "hello, the world";
	cout << a << endl;

	for (int i=0, j=a.size()-1; i<j; i++, j--) {
		char t = a[i];
		a[i]=a[j];
		a[j]=t;
	}

	cout << a << endl;

	return 0;
}
