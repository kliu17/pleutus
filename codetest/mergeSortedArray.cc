#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	nums1.insert(nums1.end(), nums2.begin(), nums2.end());
        sort(nums1.begin(), nums1.end());
    }
  
    void merge1(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	nums1.reserve(m+n);
	nums1.resize(m+n);
	while (m>0 && n>0) {
		if (nums1[m-1]>nums2[n-1]) {
			nums1[m+n-1]=nums1[m-1];
			m--;
		} else {
			nums1[m+n-1]=nums2[n-1];
			n--;
		}
	}
	if (n>0)
		for (int i=0; i<n; i++) nums1[i]=nums2[i];
    }
};

int main() {
	vector<int> nums1;
	nums1.push_back(2);
	nums1.push_back(4);
	nums1.push_back(6);
	nums1.push_back(9);

	vector<int> nums2;
	nums2.push_back(3);
	nums2.push_back(5);
	nums2.push_back(7);
	nums2.push_back(109);

	Solution s1;
	s1.merge1(nums1, nums1.size(), nums2, nums2.size());
	for (int i=0; i< nums1.size(); i++)
		cout << nums1[i] << endl;
	return 0;
}
