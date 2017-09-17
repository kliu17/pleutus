#include <iostream>
using namespace std;

class Solution {
public:
    // reverse words in a string
    void reverseWords(string &s) {
	reverse(s.begin(), s.end());
	for (int i=0, j=0; i<s.size(); i=j+1) {
		for (j=i; j<s.size() && !isblank(s[j]); j++);
		reverse(s.begin()+i, s.begin()+j);
	}
    }

    // reverse chars in each words in a string:q
    void reverseWords1(string &s) {
	for (int i=0, j=0; i<s.size(); i=j+1) {
                for (j=i; j<s.size() && !isblank(s[j]); j++);
                reverse(s.begin()+i, s.begin()+j);
        }
    }
};

int main() {
	string s = "the sky is blue, the sky is white";
	cout << s << endl;	
/*
	s.append("xyz");
	int position;
	int t=s.find("sky");
	cout << t << endl;
	cout << position <<endl;
	s=s +" ooo";
	cout << s.insert(1,"BC") << endl;
	
	int l=s.length();
	if (t!=-1) {
		string ss=s.substr(t,l);
		cout << ss << endl;
	}
*/

	Solution S1;
	S1.reverseWords(s);
	cout << s << endl;	
	return 0;
}
