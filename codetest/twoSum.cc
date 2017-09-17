#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
	public:
	
        vector<int> twosum(vector<int> nums, int t) {
		unordered_map<int, int> m;
		vector<int> res;
		for (int i=0; i<nums.size(); i++) {
			int target=t-nums[i];
			if (m.find(target) != m.end()) {
				res.push_back(nums[i]);
				res.push_back(target);
				return res;
			}
			m[nums[i]]=i;
		}
		return res;
	}

	void printArray(vector<int> res) {
		for (int i=0; i<res.size(); i++) 
			cout << res[i] << endl;
	}
};

int main() {
	vector<int> nums;
	nums.push_back(2);
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);
	nums.push_back(11);
	nums.push_back(15);
	nums.push_back(16);
	int k=31;

	Solution s;
	vector<int> res = s.twosum(nums, k); 

/*
	for(auto it: nums) cout<<it<< endl;
	cout << endl;
	for(auto p: hash)
        	cout << " " << p.first << " => " << p.second << '\n';
*/

	s.printArray(res);
	return 0;
}
