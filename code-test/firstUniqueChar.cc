#include <iostream>
#include <unordered_map>
#include <iterator>
#include <string>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> m;
/*
        for (int i=0; i< s.size(); i++) {
                unordered_map<char, int>::iterator got=m.find(s[i]);
                if (got!=m.end()) got->second++;
                else m.insert(make_pair(s[i],1));
        }
*/
	for (auto c: s)
		m[c]++;
        for (int i=0; i< s.size(); i++)
                if (m[s[i]]==1) return i;
        return -1;
    }
};

int main() {
	string s = "leetcode";
	Solution ss;
	cout<<ss.firstUniqChar(s)<<endl;
	return 0;

}

