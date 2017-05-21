#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int>& prices) {
        int minI=INT_MAX;
        int maxP=0;
        for (int i=0; i<prices.size(); i++) {
            minI=min(prices[i], minI);
            maxP=max(maxP, prices[i]-minI);
        }
        return maxP;
}

int main() {
	vector<int> p;
	p.push_back(7);
	p.push_back(1);
	p.push_back(5);
	p.push_back(3);
	p.push_back(6);
	p.push_back(4);

	cout << maxProfit(p) << endl;
	return 0;
}
