#include <iostream>
#include <queue>
#include <vector>

using namespace std;
 
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode* root) {
	vector<vector<int> > res;
	if (!root) return res;

	queue<TreeNode*> q;
	q.push(root);
	q.push(NULL);
	vector<int> v;
	while (!q.empty()) {
		TreeNode* t=q.front();
		q.pop();
		if (t==NULL) {
			res.push_back(v);
			v.resize(0);
			if (q.size()>0) q.push(NULL);
		} else {
			v.push_back(t->val);
			if (t->left) q.push(t->left);
			if (t->right) q.push(t->right);
		}
	}
	return res;
    }
};

int main() {
    Solution s;
    TreeNode a(3);
    TreeNode b(9);
    TreeNode c(20);
    TreeNode d(15);
    TreeNode e(7);
    a.left=&b;
    a.right=&c;
    c.left=&d;
    c.right=&e;
    vector<vector<int> > z=s.levelOrder(&a);
    for (int i=0; i<z.size(); i++) {
	for (int j=0; j<z[i].size(); j++)
		cout<< z[i][j] << ", ";
        cout << endl;
    }

    return 0;
}
