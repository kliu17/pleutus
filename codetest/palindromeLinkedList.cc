#include <iostream>

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
	bool isPalindrome(ListNode* head) {
	if (!head || !head->next) return true;
	ListNode * fast=head;
	ListNode * slow=head;
	while (fast->next && fast->next->next) {
		fast=fast->next->next;
		slow=slow->next;
	}        
	slow->next=reverseLinkList(slow->next);
	slow=slow->next;
	while (slow) {
		if (head->val != slow->val)
			return false;
		head = head->next;
		slow = slow->next;
	}
	return true;
    }
	
     ListNode* reverseLinkList(ListNode* h) {
     ListNode* pre=NULL;
     ListNode* cur=h;
     ListNode* curnext;
     while (cur != NULL) {
        curnext = cur->next;
        cur->next = pre;
        pre=cur;
        cur = curnext;
     }
     return pre;
	}

     void printList(ListNode *a) {
	while (a) {
		cout << a->val << endl;
		a=a->next;
	}

     }

};

int main(){
        ListNode* a = new ListNode(1);
        ListNode* b = new ListNode(2);
        ListNode* c = new ListNode(3);
        ListNode* d = new ListNode(2);
        ListNode* e = new ListNode(1);
        a->next=b;
        b->next=c;
        c->next=d;
        d->next=e;
	Solution s;
        s.printList(a);
	cout << endl << s.isPalindrome(a) << endl;

	return 0;
}
