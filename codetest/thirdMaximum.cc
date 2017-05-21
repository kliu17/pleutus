#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
	vector<int> nums;
	nums.push_back(5);
	nums.push_back(2);
	nums.push_back(2);
	nums.push_back(10);
	nums.push_back(102);
	nums.push_back(102);
	nums.push_back(1);
	nums.push_back(5);
	nums.push_back(8);

	set<int> top3;
	for (int i=0; i<nums.size(); i++) {
		top3.insert(nums[i]);
		if (top3.size()>3)
			top3.erase(top3.begin());

	}
cout << top3.size() << endl;
cout << *top3.begin() << endl;
cout << *(--top3.end()) << endl;
cout << endl;
/*
        if (top3.size()<3) return *top3.end();
        else return *(--top3.begin());
*/

	for (set<int>::iterator it=top3.begin(); it!=top3.end(); it++)
		cout << *it << endl;
	return 0;
}
