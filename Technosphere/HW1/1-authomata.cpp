#include <iostream>  
using namespace std;


int main() {
    const int coin = 5;
    int N;
    cin >> N;
    int tmp = 0;
    int res = 0; 
    int stock = 0;   
    for(int i = 0; i < N; ++i) {
        cin >> tmp;
        if(tmp == coin) {
            stock++;
        } else {
            int dif = tmp / coin - 1 - stock;
            if(dif < 0) {
                stock = -dif;
            } else {
                stock = 0;
                res += dif;
            } 
        }
    } 
    cout << res << endl;
}