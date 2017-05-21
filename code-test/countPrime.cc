#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    int countPrimes(int n) {
	if (n<=2) return 0;
	vector<bool> passed(n, false);
	int count=1;
	int l = sqrt(n);
	for (int i=3; i<n; i+=2) {
		if (!passed[i]) {
		count++;
		if (i>l) continue;
		for (int j=i*i; j<n; j+=i)
			passed[j]=true;
		}
	}
	return count;
    }

    bool isPrime(int n) {
	if (n==2) return true;
	if (n==1 || n%2==0) return false;
	for (int i=3; i < sqrt(n)+1; i+=1)
		if (n%i ==0) return false;
	return true;
    }
};

int main() {
	Solution s;
	cout<<s.countPrimes(2)<<endl;
	cout<<s.countPrimes(3)<<endl;
	cout<<s.countPrimes(10)<<endl;
	cout<<s.countPrimes(16)<<endl;

	cout << s.isPrime(9) << endl;
	cout << s.isPrime(15) << endl;
	cout << s.isPrime(10) << endl;
	cout << s.isPrime(13) << endl;
	return 0;
}
