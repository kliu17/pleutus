#include <iostream>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

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

bool hasCycle(ListNode *head) {
     if (!head || !head->next) return false;
        ListNode *sp = head;
        ListNode *fp = head;
        while (fp->next && fp->next->next) {
            sp = sp->next;
            fp = fp->next->next;
            if (sp==fp) return true;
        }
     return false;
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
	c->next=d;
	d->next=e;
	printList(a);
	cout<< endl;
	cout << hasCycle(a) << endl;
	cout << endl;
	a = reverseLinkList(a);
	cout << endl;
	printList(a);
	cleanup(a);
	return 0;
}
