#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void sort_choice_1(vector< vector< unsigned > > &matr, unsigned N, unsigned M) {
    for (unsigned startInd = 0; startInd < M - 1; ++startInd) {
		unsigned smallestInd = startInd; 
		for (unsigned currentInd = startInd + 1; currentInd < M; ++currentInd) {
			if (matr[0][currentInd] < matr[0][smallestInd]) 
				smallestInd = currentInd;
		}
 
		if(smallestInd != startInd) {
            for (unsigned i = 0; i < N; ++i) {
                swap(matr[i][startInd], matr[i][smallestInd]);
            }
        }
	} 
}

void sort_choice_2(vector< vector< unsigned > > &matr, unsigned N, unsigned M) {
    for (unsigned startInd = 1; startInd < N - 1; ++startInd) {
		unsigned smallestInd = startInd; 
		for (unsigned currentInd = startInd + 1; currentInd < N; ++currentInd) {
			if (matr[currentInd][0] < matr[smallestInd ][0]) 
				smallestInd = currentInd;
		}
 
		if(smallestInd != startInd) { 
            swap(matr[startInd], matr[smallestInd]);
        }
	} 
}

int main() { 
    vector< vector< unsigned > > matr; 
    unsigned N, M;
    cin >> N >> M;
    matr.reserve(N);
    pair< unsigned, unsigned > min;
    min.first = 1U << 31; min.second = 0; 
    for(unsigned i = 0; i < N; i++) { 
        matr[i].reserve(M);
        for(unsigned j = 0; j < M; j++) {
            cin >> matr[i][j];
            if(matr[i][j] < min.first) {
                min.first = matr[i][j];
                min.second = i;
            }
        } 
    }
    
    swap(matr[0], matr[min.second]);
    sort_choice_1(matr, N, M);
    sort_choice_2(matr, N, M);
    for(unsigned i = 0; i < N; i++) { 
        for(unsigned j = 0; j < M; j++) {
            cout << matr[i][j] << " ";
        } 
        cout << endl;
    }
    
}