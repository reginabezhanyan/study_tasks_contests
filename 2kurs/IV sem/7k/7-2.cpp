#include <iostream>

struct Result
{
    long long int res;
    public:
        Result(long long int res_ = 0) : res(res_) {}
        ~Result() {}
        
        long long int ans() {
            return res;
        }
};

void func(long long int a, long long int b, unsigned int k)
{
    if (k == 0) {
        throw Result(a + b);
    } else if ((k > 0) && (b == 1)) {
        throw Result(a);
    } else if ((k > 0) && (b > 1)) {
        try {
            func(a, b - 1, k);
        } catch(Result res) {
            try {
                func(a, res.ans(), k - 1);
            } catch(Result res) {
                throw res;
            }
        }
    }   
}

int main()
{
    long long int a, b;
    unsigned int k;
    while(std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        } catch (Result res) {   
            std::cout << res.ans() << std::endl;
        }
    } 
}