#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
	public:
	vector<string> findCommonElements(vector<string> a, vector<string> b) {
		unordered_map<string, int> m;
		vector<string> res;

		for (int i=0; i<a.size(); i++) // smaller array
			m[a[i]] ++;	

		for (int i=0; i<b.size(); i++) {
			//m[b[i]] ++;
			if (m[b[i]]) res.push_back(b[i]);
		}
		return res;
	}
};

int main() {
	Solution s;
	vector<string> a= {"abc", "bcd", "hello", "world"};
	vector<string> b= {"abc", "world"};
	vector<string> s1 = s.findCommonElements(a, b);
	for (int i=0; i<s1.size(); i++)
		cout << s1[i]<<endl;
	return 0;
}
