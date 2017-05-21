#include <iostream>
#include <queue>
using namespace std;

// moving average of the sliding window of size=wsize
class MovingAverage {
private:
	int wsize;
	queue<int> myqueue;
	double sum;

public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
	this->wsize=size;
	this->sum=0;
    }
    
    double next(int val) {
	myqueue.push(val);
	sum += val;
	int qsize=myqueue.size();
	if (qsize<=wsize) return double(sum)/qsize;
        else {
		sum -= myqueue.front();
		myqueue.pop();
		return double(sum)/wsize;
	} 
    }

    void queuePrint() {
	cout << endl;
        while (!myqueue.empty()) {
		cout << myqueue.front() << endl;
		myqueue.pop();
	}
    }
};

int main() {
	MovingAverage s(3);
	cout << s.next(10) << endl;
	cout << s.next(15) << endl;
	cout << s.next(20) << endl;
	cout << s.next(25) << endl;
	s.queuePrint();
	return 0;
}
