#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int> & A) {
        int left=0;
	int right=A.size()-1;
        int maxleft=0, maxright=0;
        int res=0;
        while (left<=right){
            if(A[left]<=A[right]){
                if(A[left]>=maxleft) maxleft=A[left];
                else res+=maxleft-A[left];
                left++;
            } else {
                if(A[right]>=maxright) maxright= A[right];
                else res+=maxright-A[right];
                right--;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> a {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << s.trap(a) <<  endl;
    return 0;
}

