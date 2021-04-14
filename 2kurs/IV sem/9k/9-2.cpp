#include <iostream>

int main()
{
    std::string buf;
    while(std::cin >> buf) { 
        char state = '0'; //State: 0,1,2,3,4,5,6,7,8
        bool fl = true;
        for(size_t i = 0; i < buf.size() && fl; i++) {
            switch(state) {
                case '0': case '1': case '5':
                    if(buf[i] == '0') {
                        state = '1';
                    } else if(buf[i] == '1') {
                        state = '2';
                    } else {
                        fl = false;
                    }
                    break;
                case '2': case '6':
                    if(buf[i] == '0') {
                        state = '3';
                    } else if(buf[i] == '1') {
                        state = '4';
                    } else {
                        fl = false;
                    }
                    break;
                case '3': case '7':
                    if(buf[i] == '0') {
                        state = '5';
                    } else if(buf[i] == '1') {
                        state = '6';
                    } else {
                        fl = false;
                    }
                    break;
                case '4': case '8':
                    if(buf[i] == '0') {
                        state = '7';
                    } else if(buf[i] == '1') {
                        state = '8';
                    } else {
                        fl = false;
                    }
                    break; 
                default:
                    break;
            }
        }
        if(!(state == '5' || state == '6' || state == '7' || state == '8')) {
            fl = false;
        }
        std::cout << fl << std::endl;
    }
}