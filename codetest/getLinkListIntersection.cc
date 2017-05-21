#include <iostream>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

ListNode *getIntersection(ListNode *headA, ListNode *headB) {
     ListNode *p1=headA;
     ListNode *p2=headB;
     if (!p1 || !p2) return NULL;
     while (p1 && p2 && p1!=p2) {
	p1=p1->next;
	p2=p2->next;
	if (p1==p2) 
		return p1;
        if (!p1) p1=headB;
	if (!p2) p2=headA;
     }
     return p1;
}

void printList(ListNode *h) {
     ListNode *t = h;
     while (t!=NULL) {
	cout << t->val << endl;
	t=t->next;
     }
}

void cleanup(ListNode *h) {
     ListNode *t = h;
     while (t!=NULL) {
	h=h->next;
	delete t;
	t=h;
     }
}

int main() {
	ListNode* a = new ListNode(1);	
	ListNode* b = new ListNode(2);	
	ListNode* c = new ListNode(3);	
	ListNode* d = new ListNode(4);	
	ListNode* e = new ListNode(5);	
	a->next=b;
	b->next=c;
	d->next=e;
	e->next=c;
	ListNode*z = getIntersection(a, d);
	cout << endl;
	cout << z->val << endl;
	cleanup(a);
	return 0;
}
