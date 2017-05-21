#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> vs;
	istringstream strcin(str);
        string s;
        while(strcin >> s) {
		vs.push_back(s);
		cout << s << endl;
	}

	if (vs.size() != pattern.size()) return false;

	map<string, char> s2c;
	map<char, string> c2s;
	for (int i=0; i<vs.size(); ++i) {
		if (s2c[vs[i]]==0 && c2s[pattern[i]]=="") {
			s2c[vs[i]]=pattern[i];
			c2s[pattern[i]]=vs[i];
			continue;
		}
		if (pattern[i] != s2c[vs[i]]) return false;
	}
	return true;
    }
};

int main() {
	Solution s;
	string p = "abba", str = "dog cat cat dog";
	cout << s.wordPattern(p, str) <<endl;
	p = "abba"; str = "dog cat cat fish";
	cout << s.wordPattern(p, str) <<endl;
	p = "aaaa"; str = "dog cat cat dog";
	cout << s.wordPattern(p, str) <<endl;
	p = "abba"; str = "dog dog dog dog";
	cout << s.wordPattern(p, str) <<endl;
	return 0;
}
