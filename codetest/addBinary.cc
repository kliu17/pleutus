#include <iostream>
#include <string>
using namespace std;

string addBinary(string a, string b) {
        string s = "";
        int c = 0, i = a.size() - 1, j = b.size() - 1;
        while(i >= 0 || j >= 0 || c == 1) {
            c += i >= 0 ? a[i --] - '0' : 0;
            c += j >= 0 ? b[j --] - '0' : 0;
            s = char(c % 2 + '0') + s;
            c /= 2;
        }
        return s;
}

int main() {
	string a="11";
	string b="1";

/*
	string binary_outputInformations;
  	for (int i = 0; i < a.size(); ++i) {
  		bitset<8> c(a.c_str()[i]);
      		binary_outputInformations+= c.to_string();
  	}
  	cout<<binary_outputInformations<<endl;
*/
	cout << addBinary(a, b) << endl;

	return 0;

}
