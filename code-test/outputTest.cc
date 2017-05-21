#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	double x=double(1)/8;
	string a = to_string(x);
	a.insert(3,"\(");
	a.insert(a.size(),")");
	cout << a << endl;
        cout << x << endl;	
        cout << setprecision(2) << x << endl;	
	return 0;
}
