#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <algorithm>

class Fac_Single
{
    Fac_Single()
    {
        factory.emplace("R", Rectangle::make);
        factory.emplace("S", Square::make);
        factory.emplace("C", Circle::make);
    }
    ~Fac_Single() {}
    Fac_Single(Fac_Single const&) = delete;  
    Fac_Single& operator= (Fac_Single const&) = delete;
    
    public:
        std::map <std::string, std::function< Figure* (const std::string &)>> factory {};
        static Fac_Single& factory_instance()
        {
            static Fac_Single s;
            return s;
        }
};

int main()
{
    std::string type, str;
    std::vector<std::unique_ptr<Figure>> p;
    Fac_Single& figures = Fac_Single::factory_instance();
    while(std::getline(std::cin, str)) {
        std::istringstream ss(str);
        ss >> type; 
        str.assign(str.begin() + str.find(type) + 1, str.end());
        p.push_back(std::unique_ptr<Figure>(figures.factory[type](str)));
    }
    std::stable_sort(p.begin(), p.end(), [] (const std::unique_ptr<Figure>& x, const std::unique_ptr<Figure>& y) {
        return x->get_square() < y->get_square();
    });
    for(auto it = p.begin(); it != p.end(); ++it) {
        std::cout << (*it)->to_string() << std::endl;
    }
    
}