#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
	unordered_map<char, int> T = { 
				   { 'I' , 1 },
                                   { 'V' , 5 },
                                   { 'X' , 10 },
                                   { 'L' , 50 },
                                   { 'C' , 100 },
                                   { 'D' , 500 },
                                   { 'M' , 1000 } };
	int total=T[s.back()];
	for (int i=s.size()-2 ; i>=0; i--) {
		if (T[s[i]] < T[s[i+1]]) total -= T[s[i]];
		else total += T[s[i]];
	}
	return total;
    }
};

int main() {
	string s="MDIVI";
	Solution s1;
	cout << s1.romanToInt(s) << endl;
	return 0;
}
