#include <iostream>
using namespace std;

int main() {
	int nums[] = {0, 1, 0, 3, 12, 8, 0, 9, 0};
	int sz = sizeof(nums)/sizeof(nums[0]);

	int index=0, last=0;
	for (int i=0; i<sz; i++) {
		if (nums[i] != 0) {
			int temp = nums[index];
			nums[index] = nums[last];
			nums[last] = temp;
			last++;
		}
		index++;
	}
	for (int i=0; i<sz; i++)
		cout<<nums[i]<<endl; 
	return 0;
}

