#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
       _capacity=capacity;
    }
    
    int get(int key) {
       auto it = cache.find(key);
       if (it == cache.end()) return -1;
       touch(it);
       return it->second.first;
    }
    
    void put(int key, int value) {
	auto it = cache.find(key);
	if (it != cache.end()) touch(it);
	else {
		if (cache.size() == _capacity) {
			cache.erase(used.back()); // remove from hash table
			used.pop_back();  // remove from list
		}
		used.push_front(key);

	}
	cache[key] = {value, used.begin()};
    }

private:
    typedef list<int> LI;
    typedef pair<int, LI::iterator> PII;
    typedef unordered_map<int, PII> HIPII;

    int _capacity;
    LI used;
    HIPII cache;

    void touch(HIPII::iterator it) {
	int key=it->first;
	used.erase(it->second.second); //delete old one
	used.push_front(key); // insert new one in the front
 	it->second.second=used.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main() {
	LRUCache cache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	cout << cache.get(1) <<endl;       // returns 1
	cache.put(3, 3);    // evicts key 2
	cout << cache.get(2) <<endl;       // returns -1 (not found)
	cache.put(4, 4);    // evicts key 1
	cout << cache.get(1) <<endl;       // returns -1 (not found)
	cout << cache.get(3) <<endl;       // returns 3
	cout << cache.get(4) <<endl;       // returns 4
	return 0;
}
