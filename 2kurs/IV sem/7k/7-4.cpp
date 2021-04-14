#include <iostream> 

int main()
{
    std::string str;
    std::cin >> str;
    unsigned i = 1;
    char state = 'S';
    bool fl = true;
    unsigned size = str.size();
     
    while((i < size) && (fl)) {
        switch (state) {
            case 'S': 
                switch(str[i]) {
                    case '0':
                        ++i;
                        break;
                    case '1':
                        state = 'A';
                        ++i;
                        break;
                    case '#':
                        fl = false;
                        break; 
                    default:
                        fl = false;
                        break;
                }
                break;
            case 'A':
                switch(str[i]) {
                    case '0':
                        ++i;
                        break;
                    case '1':
                        state = 'S';
                        ++i;
                        break;
                    case '#':
                        state = 'B';
                        --i;
                        break; 
                    default:
                        fl = false;
                        break;
                } 
                break;
            case 'B': 
                switch(str[i]) {
                    case '0':
                        --i;
                        break;
                    case '1':
                        --i;
                        break;
                    case '#':
                        state = 'C';
                        ++i;
                        break; 
                    default:
                        fl = false;
                        break;
                } 
                break;
            case 'C': 
                switch(str[i]) {
                    case '0':
                        ++i;
                        break;
                    case '1':
                        str[i] = '0';
                        state = 'D';
                        fl = false;
                        break;
                    default:
                        fl = false;
                        break;
                }
                break;
            case 'D': 
                switch(str[i]) {
                    case '0':
                        fl = false;
                        break;
                    default:
                        fl = false;
                        break;
                }
                break;
            default: 
                break;
        }
    }
    std::cout << str << std::endl;   
}