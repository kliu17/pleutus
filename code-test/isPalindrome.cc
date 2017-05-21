#include <iostream>
#include <string>
#include <bitset>
using namespace std;

class Solution {
        public:
        bool isPalindrome(string a) {
                int sz=a.size();
                for (int i=0, j=sz-1; i<j; i++, j--) {
                        while (!isalnum(a[i]) && (i<j)) i++;
                        while (!isalnum(a[j]) && (i<j)) j--;
                        if (toupper(a[i]) != toupper(a[j])) return false;
                }
                return true;
        }
	bool canPermutePalindrome(string s) {
    		bitset<256> b;
    		for (char c : s) b.flip(c);
    		return b.count() < 2;
	}
};

int main() {
        Solution b;
        string a1 = "a,  d  bcd dcba";
        string a2 = "A man, a plan, a canal: Panama";
        string a3 = "race a car";
        string a4 = "a   bcd dcba";
	string a5 = ".,";
        cout << a1 << ": " << b.isPalindrome(a1) << endl;
        cout << a2 << ": " << b.isPalindrome(a2) << endl;
        cout << a3 << ": " << b.isPalindrome(a3) << endl;
        cout << a4 << ": " << b.isPalindrome(a4) << endl;
        cout << a5 << ": " << b.isPalindrome(a5) << endl;

	cout << endl;
        cout << a1 << ": " << b.canPermutePalindrome(a1) << endl;
        cout << a2 << ": " << b.canPermutePalindrome(a2) << endl;
        cout << a3 << ": " << b.canPermutePalindrome(a3) << endl;
        cout << a4 << ": " << b.canPermutePalindrome(a4) << endl;
        cout << a5 << ": " << b.canPermutePalindrome(a5) << endl;
        return 0;
}
