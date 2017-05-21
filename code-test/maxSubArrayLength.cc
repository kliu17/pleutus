#include <iostream>
#include <unordered_map>
using namespace std;

int main() {

	int nums[] = {1, 3, 2, -1, -8, 4, 6};
	int sz = sizeof(nums)/sizeof(nums[0]);
	int k=5;

	unordered_map<int, int> sums;
	int cur_sum=0;
	int max_len=0;
	for (int i=0; i<sz; i++) {
		cur_sum+=nums[i];
		if (cur_sum==k)
			max_len=i+1;
		else if (sums.find(cur_sum - k) != sums.end()) 
			max_len=max(max_len, i-sums[cur_sum-k]);
		if (sums.find(cur_sum) == sums.end())
			sums[cur_sum]=i;

	}

	for (int i=0; i<sz; i++) cout<<nums[i] << endl;
	cout << max_len << endl << endl;
	for (auto it=sums.begin(); it!=sums.end(); ++it)
		cout << it->first << ": " << it->second << endl;
	return 0;
}
