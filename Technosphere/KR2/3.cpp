#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unsigned N;
    cin >> N;
    vector< vector <long long> > v; 
    long long x, y, z;
    
    for (unsigned i = 0; i < N; i++) {
        cin >> x >> y >> z;
        vector<long long> tmp;
        tmp.push_back(x);
        tmp.push_back(y);
        tmp.push_back(z);
        v.push_back(tmp);
    }
    sort(v.begin(), v.end()); 

    x = v[0][0] + v[N - 1][0];
    y = v[0][1] + v[N - 1][1];
    z = v[0][2] + v[N - 1][2];
            
    for (int i = 1, j = N - 2; i < j; i++, j--) {
        if ((v[i][0] + v[j][0]) != x || (v[i][1] + v[j][1]) != y || (v[i][2] + v[j][2]) != z) { 
            cout << "No" << endl;
            return 0;
        }
    }
    
    cout << "Yes" << endl;
    return 0;
}
