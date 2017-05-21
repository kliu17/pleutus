#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_map>

using namespace std;

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
	vector<int> res;

	unordered_map<int, int> hash;
	for (int i=0; i<nums.size(); i++) {
		int target = k-nums[i];
		if (hash.find(target) != hash.end()) {
			res.push_back(hash[target]); 
			res.push_back(i); 
			break;
			//return res;
		}
		//hash.insert(make_pair(nums[i], i));
		hash[nums[i]]=i;
	}
	

	for(auto it: nums) cout<<it<< endl;
	cout << endl;
	for(auto p: hash)
        	cout << " " << p.first << " => " << p.second << '\n';

	cout << endl;
	for (int i=0; i<res.size(); i++) cout << res[i] << endl;
	return 0;
}
