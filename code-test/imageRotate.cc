#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    void rotate90(vector<vector<int>>& m) {
	reverse(m.begin(), m.end());
	for (int i=0; i<m.size(); i++) {
		for (int j=i+1; j<m[i].size(); j++)
			swap(m[i][j], m[j][i]);
	}
    }

    void anticlockRotate90(vector<vector<int>>& m) {
	for (auto it: m) 
		reverse(it.begin(), it.end());
        for (int i=0; i<m.size(); i++) {
                for (int j=i+1; j<m[i].size(); j++)
                        swap(m[i][j], m[j][i]);
        }
    }

    void printMatrix(vector<vector<int>>& m) {
	for (int i=0; i<m.size(); i++) {
		for (int j=0; j<m[i].size(); j++)
			cout << m[i][j] << " ";
		cout<< endl;
	}
    }
};

int main() {
	vector<vector<int>> m {{1,2,3}, {4,5,6}, {7,8,9}};
	Solution s;
	s.printMatrix(m);

	s.anticlockRotate90(m);

	cout << endl;
	s.printMatrix(m);
	return 0;
}
