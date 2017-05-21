#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    void dumpStack(stack<char>& p) {
	while (!p.empty()) {
		cout << p.top() << " ";
		p.pop();
	}
	cout << endl;
    }

    bool isValid(string s) {
    	stack<char> p;
	for (int i=0; i< s.size(); i++) {
		switch (s[i]) {
			case '(': { p.push(s[i]); break; }
			case '{': { p.push(s[i]); break; }
			case '[': { p.push(s[i]); break; }
                        case ')': {
                                if (p.empty() || (p.top() != '(')) return false;
                                else { p.pop(); break; }
                        }
                        case '}': {
                                if (p.empty() || (p.top() != '{')) return false;
                                else { p.pop(); break; }
                        }
                        case ']': {
                                if (p.empty() || (p.top() != '[')) return false;
                                else { p.pop(); break; }
                        }
			default:
				cout << "skipped " << s[i] << endl;

		}
	}
        return p.empty(); 
    }
};

int main() {
	Solution s1;
	string str="(abc)[]{}";
	cout << s1.isValid(str) << endl;
	return 0;
}
