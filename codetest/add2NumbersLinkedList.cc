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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int t =0;
	if (l1) t += l1->val; if (l2) t += l2->val;
	int d = t / 10; 
	t = t % 10; 
	ListNode* l3 = new ListNode(t);
	ListNode* h3 = l3;
	while (l1->next && l2->next) {
		l1=l1->next; l2=l2->next; t=d; 
		if (l1) t += l1->val; if (l2) t += l2->val;
		d = t / 10; t = t % 10;
		l3->next = new ListNode(t); 
		l3 = l3->next;
	}
	while (l1->next) {
		l1=l1->next;
		t = l1->val + d;
                d = t / 10; t = t % 10;
		l3->next = new ListNode(t); 
		l3 = l3->next;
        }
	while (l2->next) {
		l2=l2->next;
		t = l2->val + d;
                d = t / 10; t = t % 10;
		l3->next = new ListNode(t); 
		l3 = l3->next;
        }
 	if (!l1->next && !l2->next && d > 0) l3->next = new ListNode(d);
	return h3;        
    }

    void printNode(ListNode *l) {
	while (l) {
		cout << l->val << endl;
		l = l->next;
	}
	cout <<  endl;
    }
};

int main() {
	Solution s;
	ListNode * l1 = new ListNode(5);
/*	ListNode * l11 = new ListNode(2);
	ListNode * l12 = new ListNode(3);
	ListNode * l13 = new ListNode(6);
*/
//	l1->next = l11;
//	l11->next = l12;
//	l12->next = l13;
	s.printNode(l1);

	ListNode * l2 = new ListNode(5);
	ListNode * l21 = new ListNode(9);
/*
	ListNode * l22 = new ListNode(4);
	ListNode * l23 = new ListNode(4);
*/
	l2->next = l21;
//	l21->next = l22;
//	l22->next = l23;
	s.printNode(l2);

	ListNode* l3 = s.addTwoNumbers(l1, l2);
	s.printNode(l3);
	return 0;
}
