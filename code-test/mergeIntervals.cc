#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for an interval.
 */
struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
	if (intervals.empty()) return vector<Interval> {};
	vector<Interval> res;
    	//sort(intervals.begin(), intervals.end());
	sort(intervals.begin(), intervals.end(), [](Interval a, Interval b){return a.start < b.start;});
	res.push_back(intervals[0]);
	for (int i=1; i<intervals.size(); i++) {
		if (intervals[i].start <= res.back().end)
			res.back().end=max(res.back().end, intervals[i].end);
		else 
			res.push_back(intervals[i]);

	}    
	return res;
    }
};

int main() {
    Interval i1(1,3);
    Interval i2(2,6);
    Interval i3(8,10);
    Interval i4 = Interval(15,18);
    vector<Interval> a;
    a.push_back(i1);
    a.push_back(i2);
    a.push_back(i3);
    a.push_back(i4);
    Solution s;
    vector<Interval> b = s.merge(a);
    for (int i=0; i<b.size(); i++) {
	cout << b[i].start << ", " << b[i].end << endl;
    }
    return 0;
}
