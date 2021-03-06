#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
	int maxi=0, count=0, ln=1;
	bool isFile=false;
	vector<int> level(200);
	level[0]=0;
	for (int i=0, fin=input.size(); i<fin; i++) {
		while (input[i]=='\t') {
			++ln; ++i;
		}
		while (input[i]!='\n' && i<fin) {
			if (input[i]=='.') isFile=true;
			++count; ++i;
		}
		if (isFile)
			maxi=max(maxi, level[ln-1]+count);
		else
			level[ln]=level[ln-1]+count+1;
		count=0; ln=1; isFile=false;
	}
	return maxi; 
    }
};

int main() {
	
	string str = "dir\\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
	Solution s1;
	cout<<s1.lengthLongestPath(str)<<endl;
	return 0;
}
