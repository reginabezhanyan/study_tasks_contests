#include <iostream>
#include <ctime>
#include <vector>

using namespace std; 

vector<vector<unsigned long long>> mult(vector<vector<unsigned long long>>& A, vector<vector<unsigned long long>>& B, unsigned long long m) {
    vector<vector<unsigned long long>> mt(2, vector<unsigned long long>(2)); 
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mt[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                mt[i][j] += A[i][k] * B[k][j];
            } 
            mt[i][j] %= m;
        }
    }
    return mt;    
}

vector<vector<unsigned long long>> pow(vector<vector<unsigned long long>>& X, unsigned long long n, unsigned long long m, vector<vector<unsigned long long>>& I) { 
    if(n == 0) {
        return I;
    }
    if(n == 1) {
        return X;
    }
    vector<vector<unsigned long long>> Y = pow(X, n / 2, m, I);
    Y = mult(Y, Y, m);
    if(n % 2) {
        Y = mult(X, Y, m);
    }
    return Y;    
}


 
unsigned long long fibo(unsigned long long N, unsigned long long M) {
    vector<vector<unsigned long long>> X(2, vector<unsigned long long>(2));
    X[0][0] = 1; X[0][1] = 1; X[1][0] = 1; X[1][1] = 0;
    vector<vector<unsigned long long>> I(2, vector<unsigned long long>(2));
    I[0][0] = 1; I[0][1] = 0; I[1][0] = 1; I[1][1] = 0;
    vector<vector<unsigned long long>> ans = pow(X, N, M, I);
    return ans[0][1];
}
 
int main() { 
    unsigned long long N;
    cin >> N;
    unsigned long long M;
    cin >> M;  
    
    cout << fibo(N, M) << endl; 
}