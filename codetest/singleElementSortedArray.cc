#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

//Given a sorted array consisting of only integers where every element appears twice except 
//for one element which appears once. Find this single element that appears only once.
// Example 1: Input: [1,1,2,3,3,4,4,8,8] Output: 2
    int singleNonDuplicate(vector<int>& nums) {
	int left=0, right=nums.size()-1;
        while (left< right) {
		int m = left+(right-left)/2;
cout << "m is " << m<<endl;
		if (m%2==0) {
			if (nums[m]==nums[m-1]) left=m-2;
			else if (nums[m]==nums[m+1]) left = m+2;
			else return nums[m];
		} else {
			if (nums[m]==nums[m-1]) left=m+1;
			else if (nums[m]==nums[m+1]) right=m-1;
		}

	}
	return nums[left];
    }
};

int main() {
    vector<int> v={1,1,2,3,3,4,4};
    Solution s;
    cout << s.singleNonDuplicate(v) << endl;

    return 0;
}
