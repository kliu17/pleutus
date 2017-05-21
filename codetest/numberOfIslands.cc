#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
	int count=0;
	for (int i=0; i<grid.size(); i++)
		for (int j=0; j<grid[i].size(); j++) 
			if (grid[i][j]=='1') {
				count++;
				clearLand(grid, i, j);
			}
	return count;
    }

    void clearLand(vector<vector<char>>& grid, int i, int j) {
	if (i<0 || j<0 || i>grid.size() || j>grid[i].size() || grid[i][j]=='0') return;
	grid[i][j]='0';
	clearLand(grid, i+1, j);
	clearLand(grid, i-1, j);
	clearLand(grid, i, j+1);
	clearLand(grid, i, j-1);
	return;
    }
};

int main() {
	vector<char> va {'1', '1', '1', '1', '0'};
	vector<char> vb {'1', '1', '0', '1', '0'};
	vector<char> vc {'1', '1', '0', '0', '0'};
	vector<char> vd {'1', '1', '1', '1', '0'};
	vector<char> ve {'0', '0', '0', '0', '0'};
	vector<vector<char>> g {va, vb, vc, vd, ve};

	Solution s;
	cout << s.numIslands(g) <<endl;
	return 0;
}
