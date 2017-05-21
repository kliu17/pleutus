#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
	string cmap[10] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};	
	vector<string> res;
	res.push_back("");
	for (int i=0; i<digits.size(); i++) {
		vector<string> tvector;
		string c = cmap[digits[i]-'0'];
		for (int j=0; j<c.size(); j++)
			for (int k=0; k<res.size(); k++) {
				string t = res[k]+c[j];
				tvector.push_back(t);
			}
		res = tvector;
	}
	return res;
    }
	
};

int main() {
	Solution A;
	vector<string> a = A.letterCombinations("432");
	for (int i=0; i<a.size(); i++)
		cout << a[i] << endl;
	return 0;
}
