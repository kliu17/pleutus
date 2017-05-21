#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        stack<int> s;
        unordered_map<int, int> m;
        for (int n : nums) {
            while (s.size() && s.top() < n) {
                m[s.top()] = n;
                s.pop();
            }
            s.push(n);
        }

	cout << "stack s" << endl;
	while (!s.empty()) { cout << s.top() << endl; s.pop(); }

	cout << "map m" << endl;
	for (auto it=m.begin(); it!=m.end(); it++) cout << it->first << " " << it->second << endl;

        vector<int> ans;
        for (int n : findNums) ans.push_back(m.count(n) ? m[n] : -1);
        return ans;
    }
};


int main() {
	Solution s;
	vector<int> findNums {4,1,2};
	vector<int> nums {1,3,4,2};
	vector<int> r = s.nextGreaterElement(findNums, nums);
	cout << endl;
	for (int i=0; i<r.size(); i++)
		cout << r[i]<<endl;
	return 0;
}
