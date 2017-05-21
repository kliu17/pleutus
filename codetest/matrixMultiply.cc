#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector< vector<int> > multiply(vector< vector<int> >& A, vector< vector<int> >& B) {
	int m=A.size();
	int n=A[0].size();
	int z=B[0].size();
	vector< vector<int> > C(m, vector<int>(z,0));

 	for(int i=0; i<m; i++) {
            for(int k=0; k<n; k++) {
		if(A[i][k] != 0)
            	  for(int j=0; j<z; j++)
		 	C[i][j] += A[i][k]*B[k][j];
            }
    	}
	return C;
    }

    void vectorPrint(vector< vector<int> >& C) {
	for (int i = 0; i < C.size(); i++) {
    		for (int j = 0; j < C[i].size(); j++)
		        cout << C[i][j] << " ";
		cout << endl;
	};
    }
};

int main() {
	vector< vector<int> > A{ {1, 0, 0}, {-1, 0, 3} };
	vector< vector<int> > B{ {7, 0, 0}, {0, 0, 0}, {0, 0, 1} };

/*
cout << A.size()<<endl;
cout << A[0].size()<<endl;
cout << A[0][1] << endl;
cout << B.size()<<endl;
*/
	Solution S;
	vector< vector<int> > C = S.multiply(A, B);
	
	S.vectorPrint(A);
	cout << endl;
	S.vectorPrint(B);
	cout << endl;
	S.vectorPrint(C);

	vector< vector<int> > aa(4, vector<int>(3, -1));
	for (int ii=0; ii<aa.size(); ii++)  {
		for (int j = 0; j < C[ii].size(); j++)
			cout << aa[ii][j] << " ";
		cout << endl;
	}
	return 0;
}
