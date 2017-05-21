#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printTree(TreeNode* root) {
	if (root!=NULL) {
		cout << root->val << endl;
		printTree(root->left);
		printTree(root->right);
	}
}

int sumLeftLeaves(TreeNode* root, bool isLeft=false) {
	if (!root) return 0;
	if (!root->left && !root->right) return isLeft ? root->val : 0;
	return sumLeftLeaves(root->left, true) + sumLeftLeaves(root->right, false);
}

void getTreePaths(vector<string> &res, TreeNode* root, string z) {
	if (!root->left && !root->right) {
		res.push_back(z);
		return;
	}
	if (root->left) getTreePaths(res, root->left, z+"->"+ to_string(root->left->val));
	if (root->right) getTreePaths(res, root->right, z+"->"+  to_string(root->right->val));
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        return root;
}

vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
	if (!root) return res; 
	getTreePaths(res, root, to_string(root->val));
	return res;
}

int getTreeLevel(TreeNode * node, int data, int level) {
	if (node == NULL) return 0;
	if (data == node->val) return level;
	
	int leveldown=getTreeLevel(node->right, data, level+1);
	if (leveldown != 0) return leveldown;
	leveldown = getTreeLevel(node->left, data, level+1);
	return leveldown;

}

int getLevel(TreeNode *node, int data) {
	return getTreeLevel(node, data, 1);
}

int main() {
	TreeNode* a = new TreeNode(15);
	TreeNode* b = new TreeNode(7);
	TreeNode* c = new TreeNode(20);
	TreeNode* f = new TreeNode(9);
	TreeNode* g = new TreeNode(3);
	TreeNode* d = new TreeNode(18);
	TreeNode* e = new TreeNode(22);
	a->left=b;
	a->right=c;
	c->left=d;
	c->right=e;
	b->left=g;
	b->right=f;
	printTree(a);
	cout << endl;
	cout << getLevel(a, 15) << endl;
	cout << getLevel(a, 22) << endl;
	cout << getLevel(a, 7) << endl;
	cout << endl;
	cout << endl << sumLeftLeaves(a) << endl;

        vector<string> r= binaryTreePaths(a);
	for (auto i: r) cout << i << endl;

	TreeNode * z = lowestCommonAncestor(a, b, e);
	cout << "LCA " << z->val << endl;
	return 0;

}
