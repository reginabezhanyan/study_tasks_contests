#include <iostream>
#include <vector>
#include <map>
#include <cctype>

void do_reach(char cur, std::vector <char>& left, std::vector <std::string>& right, std::map<char, bool>& Mv)
{
    for(size_t i = 0; i < left.size(); ++i) {
        if(left[i] == cur) {
            for(size_t j = 0; j < right[i].size(); ++j) {
                if(isupper(right[i][j])) {
                    auto it = Mv.find(right[i][j]);
                    if(it != Mv.end()) {
                        if(!((*it).second)) {
                            (*it).second = true;
                            do_reach(right[i][j], left, right, Mv);
                        }
                    }
                }
            }
        }
    }
}



int main()
{
    std::vector <std::string> right;
    std::vector <char> left; 
    std::map<char, bool> Mv;
    char buf1;
    std::string buf2;
    Mv.insert(std::pair<char, bool>('S', true));
    while(std::cin >> buf1 >> buf2) {
        left.push_back(buf1);
        right.push_back(buf2);
        Mv.insert(std::pair<char, bool>(buf1, false));
    }
    do_reach('S', left, right, Mv);
    for(size_t i = 0; i < left.size(); ++i) {
        if((*(Mv.find(left[i]))).second) {
            std::cout << left[i] << " " << right[i] << std::endl;
        }
    }
}