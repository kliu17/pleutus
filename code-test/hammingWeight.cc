#include <iostream>
using namespace std;

class Solution {
	public:
	int hammingWeight(uint32_t n) {
		int count =0;
		while (n) {
			n &= (n-1);
			count++;
		}

		return count;
	}
	int hammingDistance(int x, int y) {
		int dist=0;
		int n = x ^ y;
		while (n) {
			n &= (n-1);
			dist++;
		}
	 	return dist;	
	}

};


int main() {
	int n=11;
	Solution s;
	cout<<s.hammingWeight(n)<<endl;

	int x=1, y=4;
	cout<<s.hammingDistance(x,y)<<endl;
	return 0;
}

