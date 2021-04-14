#include <iostream>
#include <sstream>
#include <cmath>
#include "boost/date_time/gregorian/gregorian.hpp"

int main()
{
    
    std::string str_date;
    unsigned y, m, d;
    unsigned long long ans = 0;
    if(std::cin >> str_date) {
        std::istringstream ss(str_date);
        ss >> y;
        ss.ignore();
        ss >> m;
        ss.ignore();
        ss >> d;
    }
    boost::gregorian::date date1(y, m, d);
    while(std::cin >> str_date) {
        std::istringstream ss(str_date);
        ss >> y;
        ss.ignore();
        ss >> m;
        ss.ignore();
        ss >> d;
        boost::gregorian::date date2(y, m, d);
        ans += abs((date1 - date2).days());
        date1 = date2;
    }
    std::cout << ans << std::endl;
}