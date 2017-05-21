#include <iostream>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> ms;
    stack<int> s;
    
public:    
    MinStack() {
    }
    void push(int x) {
        s.push(x);
        if (ms.empty() || x<=getMin()) ms.push(x);
    }

    void pop() {
        if (s.top() == getMin()) {
                ms.pop();
        }
        s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        if (!ms.empty())
            return ms.top();
        else 
            return 0;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */


int main() {
	MinStack obj;
	obj.push(-2);
	obj.push(0);
	obj.push(-3);
	int p4=obj.getMin();
	cout << p4 << endl;
	obj.pop();
	int p3=obj.top();
	cout << p3 << endl;
	cout << obj.getMin()<< endl;
	return 0;
}
