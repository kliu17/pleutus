#include <iostream>
#include <forward_list>
using namespace std;
/**
 * Definition for singly-linked list.
 */

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
       ListNode dummy(INT_MIN);
        ListNode *temp = &dummy;

        while (l1 && l2) {
                if (l1->val > l2->val) {
                        temp->next = l2;
                        l2 = l2->next;
                } else {
                        temp->next = l1;
                        l1 = l1->next;
                }
                temp=temp->next;
        }
        temp->next = l1 ? l1 : l2;
        return dummy.next;
    }
};

int main() {
	forward_list<int> alist;
	alist.push_front(1);	
	alist.push_front(8);	
	alist.push_front(10);	
	for (int& x: alist) std::cout << ' ' << x;
	cout << endl;
	forward_list<int> blist;
	alist.push_front(3);	
	alist.push_front(7);	
	alist.push_front(14);	

	ListNode a = ListNode(1);
	ListNode b = ListNode(2);
	Solution s;
	ListNode *clist = s.mergeTwoLists(&a, &b);
	while (clist) {
		cout << clist->val <<endl;
		clist = clist->next;
	}
	return 0;
}
