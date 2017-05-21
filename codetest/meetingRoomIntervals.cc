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
// Given a collection of intervals, merge all overlapping intervals.
// For example, Given [1,3],[2,6],[8,10],[15,18], return [1,6],[8,10],[15,18].
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

// number of rooms needed
    int minMeetingRooms(vector<Interval>& intervals) {
	vector<int> starts, ends;
	for (auto itr: intervals) {
		starts.push_back(itr.start);
		ends.push_back(itr.end);
	}
	sort(begin(starts), end(starts));
	sort(begin(ends), end(ends));

	int e=0, rooms=0, available=0;
	for (int s: starts) {
		while (ends[e] <=s) {
			++e;
			++available;
		}
		if (available) --available;
		else ++rooms;
	}
	return rooms;
   }


// Given an array of meeting time intervals consisting of start and 
// end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.
// For example, Given [[0, 30],[5, 10],[15, 20]], return false.
    bool canAttendMeetings(vector<Interval>& intervals) {
	sort(intervals.begin(), intervals.end(), [](const Interval& i1, const Interval& i2){
                return i1.start < i2.start; });
        for (int i=1; i<intervals.size(); i++)
		if (intervals[i].start<intervals[i-1].end) return false;
	return true; 
    }


// Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
// You may assume that the intervals were initially sorted according to their start times.
// Example 1: Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
// Example 2: Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    	vector<Interval> ret;
    	//auto it = intervals.begin();
    	for(auto it = intervals.begin(); it!=intervals.end(); ++it){
		if(newInterval.end < (*it).start) //all intervals after will not overlap with the newInterval
			break; 
		else if(newInterval.start > (*it).end) //*it will not overlap with the newInterval
			ret.push_back(*it); 
       		else{ //update newInterval bacause *it overlap with the newInterval
       	     		newInterval.start = min(newInterval.start, (*it).start);
            		newInterval.end = max(newInterval.end, (*it).end);
   		}	
    	}

    	// don't forget the rest of the intervals and the newInterval
	ret.push_back(newInterval);
	for(auto it = intervals.begin(); it!=intervals.end(); ++it)
		ret.push_back(*it);
	return ret;
    }
};

int main() {
	Interval a1 = Interval(1,3);
	Interval a2 = Interval(2,5);
	Interval a3 = Interval(3,4);
	Interval a4 = Interval(3,6);

	vector<Interval> intervals;
	intervals.push_back(a1);
	intervals.push_back(a2);
	intervals.push_back(a3);
	intervals.push_back(a4);

	Solution A;
	cout << A.minMeetingRooms(intervals) << endl;
	cout << A.canAttendMeetings(intervals) << endl;

        Interval newInterval(9,10);
        vector<Interval> v=A.insert(intervals, newInterval);
	cout << endl;
	for (int i=0; i<v.size(); i++) cout <<v[i].start << ", " << v[i].end<< endl;

        v = A.merge(intervals);
	cout << endl;
	for (int i=0; i<v.size(); i++) cout <<v[i].start << ", " << v[i].end<< endl;
	return 0;
}
