#include <iostream>
using namespace std;

class myset {
public:
  myset(size_t n) {// Конструктор. Метод абстракции create
    const size_t els = (n+31)/32;
    body = new unsigned[els];
    this->n = n;
    for (size_t i = 0; i < els; i++) {
      body[i] = 0;
    }
  }

  ~myset() {       // Деструктор.  Метод destroy
    delete [] body;
  }

  void insert(size_t el) {
    if (el >= n) return;
    body[el / 32] |= (1 << (el % 32));
  }

  void erase(size_t el) {
    if (el >= n) return;
    body[el / 32] &= ~(1 << (el % 32));
  }

  bool in(size_t el) {
    if (el >= n) return false;
    return (body[el / 32] >> (el % 32)) & 1;
  }
private:
  unsigned *body;
  size_t n;   
};

void pr(myset &prime) {
    for(int i = 2; i < 20000000; i++) {
        if(prime.in(i)) {
            unsigned p = i;
            while(p < 20000000) {
                prime.insert(p);
                p += i;
            }
        }  
    }
}

int main() {
    unsigned int start_time =  clock(); // начальное время
    myset prime(20000000); 
    unsigned M, N;
    cin >> M >> N;
    unsigned ans = 0;
    pr(prime); 
    for(unsigned i = 2; i < N + 2; i++) {
        if(prime.in(i)) ans++;
    }
    cout << ans << endl;
    if(M == ans) {
        cout << 2 << endl;
        return 0;
    } 
    unsigned MAX = 20000000 - N;
    for(unsigned i = 3; i <= MAX; i++) {
        if(!prime.in(i - 1)) ans--;
        if(!prime.in(i + N - 1)) ans++;
        if(M == ans) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    
    unsigned int end_time = clock(); // конечное время
    cout <<  (double) (end_time - start_time) / CLOCKS_PER_SEC << endl;
} 