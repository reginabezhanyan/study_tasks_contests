#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Average {
    double sum_;
    int n_;
public:
    Average() : sum_(0), n_(0) {}
    void operator()(double x) {
        sum_ += x;
        ++n_;
    }
    double result() const { return sum_ / n_; }
};

int main()
{
    std::vector <double> v;
    double x;
    while(std::cin >> x)
    {
        v.push_back(x);
    }
    size_t size = v.size();
    size_t l = size * 0.1;
    std::sort(v.begin() + l, v.end() - l);
    size = size - (l << 1);
    l += size * 0.1; 
    Average ans;
    ans = std::for_each(v.begin() + l, v.end() - l, ans);
    std::cout << std::setprecision(10) << ans.result() << std::endl;
}