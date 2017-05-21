#include <iostream>
#include <vector>

using namespace std;

class Solution {
	public:
        int getIndex(int i, vector<int> nums) {
                int n= nums.size();
                if (i+nums[i] > 0) return (i+nums[i])%n;
                else return n+((i+nums[i]) %n);
        }

	bool circularArrayLoop(vector<int> nums) {
		int n=nums.size();
		for (int i=0; i<n; i++) {
			if (nums[i] == 0) continue;
			
			// slow and fast pointer
			int j=i, k=getIndex(i, nums);
			while (nums[k]*nums[i] && nums[getIndex(k,nums)]*nums[i] >0) {
				if (j==k) {
					if (j==getIndex(j, nums)) break;
					return true;
				}
				j=getIndex(j, nums);
				k=getIndex(getIndex(k, nums),nums);
			}
			j=i;
			int val=nums[i];
			while (nums[j]*val>0) {
				int next=getIndex(j,nums);
				nums[i]=0;
				j=next;
			}
		}
		return false;
	}

};

int main() {

	return 0;
}
