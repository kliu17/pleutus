#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
	vector<int> v(rowIndex+1, 0);
	v[0]=1;
	for (int i=1; i<rowIndex+1; i++) {
		for (int j=i; j>=1; j--) {
			v[j] += v[j-1];
cout << "V[" << j <<"]="<<v[j]<<endl;
		}
		cout << endl;
	}
        
	return v;
    }
   
};

int main() {
	vector<int> a;
	Solution s;
	a=s.getRow(5);
	for (int i=0; i<a.size(); i++)
		cout << a[i] << endl;

	return 0;
}
