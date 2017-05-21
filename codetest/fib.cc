#include <iostream>
#include <vector>

using namespace std;

class Solution {
	public:
	int fib(int n) {
		vector<int> a(n+1, -1);
		a[1]=1;
		int b = fib1(n,a);
		for (int i=1; i<n+1; i++) cout << a[i] << endl;
		return b;
	}

	int fib1(int n, vector<int> &a) {
		if (n==0 || n==1) return n;
		if (a[n] == -1) a[n]=fib1(n-1, a)+fib1(n-2, a);
		return a[n];
	}
};

int main() {
	Solution s;
	cout << s.fib(15) << endl;
	return 0;
}
