#include <map>
#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> m1;

    m1.size();
    m1["a"] = 10;

    std::cout << m1["a"] << std::endl;
    std::cout << m1["b"] << std::endl; // значение 0

    std::cout << m1.count("b") << std::endl;
    std::cout << m1.count("c") << std::endl; //True - False


    {
        std::map<std::string, int>::iterator it = m1.find("a");
        if (it != m1.end()) {
            std::cout << it->second << std::endl;
        }
    }
    //можно заключить в {}

    if (auto it = m1.find("a"); it != m1.end()) {
        std::cout << it->second << std::endl;
    }

    auto const &m2 = m1;
  //  std::cout << m2["a"] << std::endl; //не сработает

    if (auto it = m2.find("a"); it != m1.end()) {
       std::cout << it->second << std::endl;
    }

    m1.insert({ "d", 100500 });
    std::cout << m1["d"] << std::endl;

    static const std::map<double, int> m3 {
                { 3.4, 2},
                { 1.2, 11},
    }

    std::pair<bool, double> p1{true, 3.14};
    std::cout << p1.first << "," << p1.second << std::endl;

    for(auto i = m2.begin(); it != m2.end();++it) {
        std::cout << it->first << "," << it->second << std::endl;
    }


    for (const auto &p : m2) {
        std::cout << p.first << "," << p.second << std::endl;
    }

    std::pair p2{true, 2.71};
    auto p3 = std::makepair(true, 44.4);

    for (auto& [ key, value ] : m2) {
        std::cout << key << "," << value << std::endl;
        //value += 2; // не сработает. Неявно const перешел в value
    }
    

}