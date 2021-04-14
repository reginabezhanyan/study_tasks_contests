#include <vector>
#include <iostream>
#include <string>

int main()
{
    std::vector v1{1, 2, 3};
    std::vector<std::string> v2{"a", "b", "c"};
    std::vector<double> v3(10, 0.5);
    
    std::cout << v2.size() << "," << v2.capacity() << std::endl; //размер, размер выделенной памяти
    /*
    double z;
    while(std::cin >> z) {
        v3.push_back(z);
        std::cout << v3.size() << "," << v3.capacity() << std::endl;
    }
    
    v3.erase(v3.begin(), v3.begin() + 3);
    std::cout << v3.size() << "," << v3.capacity() << std::endl;
    
    v3.shrink_to_fit();
    std::cout << v3.size() << "," << v3.capacity() << std::endl;
    */
    v2.insert(v2.begin(), v2.begin(), v2.end());
    for(const auto &s : v2) {
        std::cout << s << std::endl;
    }
    std::cout << v2.size() << "," << v2.capacity() << std::endl;
}
