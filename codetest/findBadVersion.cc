#include <iostream>
#include <vector>
using namespace std;

int bsearch(vector<int> a, int b) {
	int low=0;
	int high=a.size();
	int m;
	while (low < high) {
		m=low+(high-low)/2;
		if (a[m]>b)
			high=m;
		else if (a[m]<b)
			low=m+1;
		else 
			return m;
	}
	return -1;
}

int main() {
	vector<int> aa;
	aa.push_back(1);
	aa.push_back(3);
	aa.push_back(4);
	aa.push_back(5);
	aa.push_back(6);
	aa.push_back(7);
	aa.push_back(37);
	cout << bsearch(aa, 3) << endl;
	cout << bsearch(aa, 7) << endl;
	cout << bsearch(aa, 373) << endl;
	
	return 0;
}
