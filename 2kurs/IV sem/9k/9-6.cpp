#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::map <std::pair<std::string,char>, std::string> Mv;
    std::string cur, neww;
    char charr;
    while(1) {
        std::cin >> cur;
        if(cur == "END") {
            break;
        }
        std::cin >> charr >> neww;
        Mv.insert(std::pair<std::pair<std::string,char>, std::string>(std::pair<std::string,char>(cur, charr), neww));
    } 
    std::vector <std::string> ok;
    while(1) {
        std::cin >> cur;
        if(cur == "END") {
            break;
        }
        ok.push_back(cur);
    }
    std::cin >> cur;
    std::string buf;
    std::cin >> buf;
    size_t i = 0;
    bool fl = true;
    for(; i < buf.size(); ++i) {
        auto it = Mv.find(std::pair<std::string,char>(cur, buf[i]));
        if(it == Mv.end()) {
            fl = false;
            break;
        }
        cur = (*it).second;
    }
    if(std::find(ok.begin(), ok.end(), cur) == ok.end()) {
        fl = false;
    }
    std::cout << fl << std::endl;
    std::cout << i << std::endl;
    std::cout << cur << std::endl; 
}