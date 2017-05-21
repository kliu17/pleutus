#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> findAnagrams(string s, string t) {
                vector<int> sv(256,0), tv(256,0), res;
                if (s.size() < t.size()) return res;
                for (int i=0; i<t.size(); i++) {
                        sv[s[i]]++;
                        tv[t[i]]++;
                }
                if (sv == tv)
                        res.push_back(0);
                for (int j=t.size(); j<s.size(); j++) {
                        sv[s[j]]++;
                        sv[s[j-t.size()]]--;
                        if (sv== tv)
                                res.push_back(j-t.size()+1);
                }
                return res;
	}

        // check 2 strings to see they are anagram of each other
        // Given two strings s and t, write a function to determine if t is an anagram of s.
        bool isAnagram(string s, string t) {
		if (s.length() != t.length()) return false;
		unordered_map<char, int> charcount;
		for (int i=0; i<s.length(); i++) {
			charcount[s[i]]++;
			charcount[t[i]]--;
		}
		for (auto c: charcount)
			if (c.second) return false;
		return true;
	}

	void dumpVector(vector<int> v) {
		for (int i=0; i<v.size(); i++)
			cout << v[i]<< " ";
		cout << endl;
	}

};


int main() {
	Solution z;
	vector<int> v;
	v=z.findAnagrams("cbaebabacd","abc");
	z.dumpVector(v);

	cout << z.isAnagram("anagram","nagaram") << endl;
	return 0;

}
