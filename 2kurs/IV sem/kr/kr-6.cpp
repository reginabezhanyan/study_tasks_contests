#include <iostream>
#include <cctype>

int lex(const std::string& s) {
    enum state {H, A, C, S, AB, CS, ER}; 
    enum  state ST = H; 
    for (size_t i = 0; i < s.size(); ++i) {
        switch(ST) {
            case H:
                if (s[i] == 'a') {
                    ST = C;
                } else if (s[i] == 'b') {
                    ST = A;
                } else {
                    ST = ER;
                }
                break;
            case C:
                if (s[i] == 'c') {
                    ST = A;
                } else {
                    ST = ER;
                }
                break;
            case A:
                if (s[i] == 'a') {
                    ST = S;
                } else {
                    ST = ER;
                }
                break;
            case S:
                if (s[i] == 'a') {
                    ST = AB;
                } else {
                    ST = ER;
                }
                break;
            case AB:
                if(s[i] == 'a') {
                    ST = S;
                } else if (s[i] == 'b') {
                    ST = CS;
                } else  if (s[i] == 'c') {
                    ST = A;
                } else {
                    ST = ER;
                }
                break;
            case CS:
                if (s[i] == 'a') {
                    ST = AB;
                } else if (s[i] == 'c') {
                    ST = A;
                } else {
                    ST = ER;
                }
                break;
            case ER:
                return 0;
            default:
                break;
        }
    }
    if (CS == S || CS == CS) {
        return 1;
    } else {
        return 0;
    }
}

int main()
{
    char c;
    std::string s = "";
    while (std::cin >> c) {
        if (!isspace(c)) {
            s = c + s;
        }
    }
    std::cout << lex(s) << std::endl; 
}