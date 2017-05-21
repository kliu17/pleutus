#include <iostream>
#include <vector>
#include <map>
#include <queue>

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
    void printTree(TreeNode * root) {
	if (root) { 
		printTree(root->left);
		cout << root->val << endl;
		printTree(root->right);
	}
    }

    vector< vector<int> > verticalOrder(TreeNode* root) {
	vector< vector<int> > output;
    	if(!root){ return output; }
    	map<int, vector<int>> m;
    	queue<pair<int, TreeNode*>> q;
    	q.push(make_pair(0,root));
    	while(!q.empty()){
        	int size = q.size();
        	for(int i = 0;  i < size; i++){
            		TreeNode* t = q.front().second;
            		int tmp = q.front().first;
            		q.pop();
            		m[tmp].push_back(t->val);
            		if(t->left){
               	 		q.push(make_pair(tmp - 1, t->left));
            		}
            		if(t->right){
               	 		q.push(make_pair(tmp + 1, t->right));
            		}
       		} 
    	}
    	for(auto& v : m){
        	output.push_back(v.second);
    	}
    	return output;
    }

    TreeNode * lowestCommonAncestor(TreeNode * root, TreeNode* p, TreeNode* q) {
	if (!root || root==p || root==q) return root;
	TreeNode* left=lowestCommonAncestor(root->left, p, q);
	TreeNode* right=lowestCommonAncestor(root->right, p, q);
	return !left ? right : !right ? left : root;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
	if (root==nullptr) return "#";
	return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
	return mydeserialize(data);
    }

    TreeNode* mydeserialize(string& data) {
        if (data[0]=='#') {
            if(data.size() > 1) 
		data = data.substr(2);  // update the new string to remove the "#,"
            return nullptr;
        } else {
            TreeNode* node = new TreeNode(helper(data));
            node->left = mydeserialize(data);
            node->right = mydeserialize(data);
            return node;
        }
    }

private:
    int helper(string& data) {
        int pos = data.find(',');
        int val = stoi(data.substr(0,pos)); // parse the string to get the node value
        data = data.substr(pos+1);	    // update the remaining string
        return val;
    }
};


int main() {
        TreeNode* a = new TreeNode(3);
        TreeNode* b = new TreeNode(9);
        TreeNode* c = new TreeNode(20);
        TreeNode* d = new TreeNode(15);
        TreeNode* e = new TreeNode(7);
        a->left=b;
        a->right=c;
        c->left=d;
        c->right=e;

	Solution AA;
        AA.printTree(a);
	vector< vector<int> > OO;
	OO=AA.verticalOrder(a);

	cout << endl;
	for (const vector<int> &v : OO) {
   		for (int x : v) 
			cout << x << ' ';
   		cout << endl;
	}
        
	TreeNode* z = AA.lowestCommonAncestor(a, b, e);
	cout << endl << z->val << endl;
	
	string serializedTree = AA.serialize(a);
	cout << endl << serializedTree << endl;
	//int index = serializedTree.find(',');
	//string s1 = serializedTree.substr(index+1);
	//cout << s1<< endl;
	TreeNode* aa= AA.deserialize(serializedTree);
        AA.printTree(aa);
	return 0;
}
