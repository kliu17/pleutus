#include <iostream>
#include <vector>
using namespace std;

int f(int n) {
	if (n==0 || n==1) return n;
	return f(n-1) + f(n-2);
}

int f1(int n, vector<int> m) {
	if (n==0 || n==1) return n;
	if (m[n]==-1) m[n]=f1(n-1, m)+f1(n-2, m);
	return m[n];	 
}

int f1(int n) {
	vector<int> m(n+1, -1);
	return f1(n, m);
}

int main() {
	cout << f(15) << endl;
	cout << f1(15) << endl;
	return 0;
}
