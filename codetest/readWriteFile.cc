#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream myfile("example.txt");
	if (myfile.is_open()) {
		myfile << "this is a lije. \n";
		myfile << "this is another line.\n";
		myfile.close();
	} else
		cout << "unable to open file" << endl;


	ifstream infile("example.txt");
	string line;
	if (infile.is_open()) {
		while (getline(infile,line)) 
			cout << line << endl;
		infile.close();
	}

        //string myteststring;
	//cin>> myteststring;
	//cout << myteststring << endl;
	return 0;
}
