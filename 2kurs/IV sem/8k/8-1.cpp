#include <iostream>

int main()
{
    bool fg = true; 
    std::string buf;
    while(std::cin >> buf) {
        for (size_t i = 0; i < buf.size(); i++) {
            if((buf.at(i) == '3') || (buf.at(i) == '4')) {
                if(fg == false) { 
                    break;
                }
            } else if((buf.at(i) == '1') || (buf.at(i) == '2')) { 
                fg = false;
            } else {
                fg = false;
                break;
            } if (i == buf.size() - 1) {
                fg = true;
            }
        }
        std::cout << fg << std::endl;
        fg = true; 
    }
}