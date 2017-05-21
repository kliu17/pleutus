#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
	vector<string> res;
	if (nums.size()<=0) return res;
	for (int i=0; i<nums.size(); i++) {
		int start=i;
		int end=i;
		while ((end+1<nums.size()) && (nums[end+1] == nums[end]+1)) {
			end++;
		}
		if (end>start) 
			res.push_back(to_string(nums[start])+"->"+to_string(nums[end]));
		else
			res.push_back(to_string(nums[start]));
		i=end;
	}
	return res;
    }
};

int main() {
    vector<int> v = {0,1,2,4,5,7};
    Solution s;
    vector<string> str = s.summaryRanges(v);
    for (int i=0; i<str.size(); i++) cout << str[i] << endl;
    return 0;
}
