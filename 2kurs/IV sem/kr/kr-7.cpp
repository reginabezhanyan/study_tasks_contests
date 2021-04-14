#include <iostream>
#include <cctype>

int B(std::string& s) {
    if (s.size() == 0) {
        return 1;
    }
    char c = s[0];
    s.erase(0, 1);
    if (c == 'b') {
        return B(s);
    } else if (c == 'd') {
        return 1;
    } 
    return 0;
}

int A(std::string& s) {
    char c = s[0];
    s.erase(0, 1);
    if (c == 'c') {
        if (A(s) && s[0] == 'd') {
            s.erase(0, 1);
            return 1;
        }
        return 0;
    } else if (c == 'e') {
        return 1;
    }
    return 0;
}
 
int S(std::string& s) {
    char c = s[0];
    s.erase(0, 1);
    if (c == 'a') {
        if (A(s) && s[0] == 'b') {
            s.erase(0, 1);
            return 1;
        }
        return 0;
    } else if (c == 'c') {
        return B(s);
    }
    return 0;
}

int main() {
    char c;
    std::string s = "";
    while (std::cin >> c) {
        if (!isspace(c)) {
            s += c;
        } 
    }
    try {
        int ans = S(s);
        if (s.size() != 0) {
            std::cout << 0 << std::endl;
        } else {
            std::cout << ans << std::endl;
        }
    } catch(...) {
        std::cout << 0 << std::endl;
    }
    return 0;
}