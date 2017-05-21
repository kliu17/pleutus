
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
	vector<string> res;
	int pre=lower-1;
        for (int i=0; i<=nums.size(); i++) {
		int cur;
		if (i==nums.size())
			cur=upper;
		else 
			cur=nums[i];
		if (cur-pre >= 2) {
			if ((pre+1) != (cur-1))
				(cur==upper) ? res.push_back(to_string(pre+1)+"->"+to_string(cur)) : res.push_back(to_string(pre+1)+"->"+to_string(cur-1));
			else
				res.push_back(to_string(pre+1));
		}
		pre=cur;
	}
	return res;
    }
};

int main() {
    vector<int> v= {0, 1, 3, 50, 75};
    int lower = 0, upper = 99;
    Solution s;

    vector<string> res=s.findMissingRanges(v, lower, upper);
    for (int i=0; i<res.size(); i++) cout << res[i] << endl;
}

