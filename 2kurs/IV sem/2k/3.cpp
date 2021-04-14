#include <iostream> 
#include <vector>
#include <map>

namespace numbers
{
    std::map <std::string, void (*) (complex_stack &)> m = {
        {"+", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp += +st;
            st = ~st;
            st = st << tmp;
        } },
        {"-", [] (complex_stack &st) {
            complex tmp = +st;
            tmp = -tmp;
            st = ~st;
            tmp += +st;
            st = ~st;
            st = st << tmp;
        } },
        {"*", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp *= +st;
            st = ~st;
            st = st << tmp;
        } },
        {"/", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp = +st / tmp;
            st = ~st;
            st = st << tmp;
        } },
        {"!", [] (complex_stack &st) {
            complex tmp = +st;
            st = st << tmp;
        } },
        {";", [] (complex_stack &st) {
            st = ~st;
        } },
        {"~", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp = ~tmp;
            st = st << tmp;
        } },
        {"#", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp = -tmp;
            st = st << tmp;
        } },
    };
    
    complex eval(const std::vector<std::string> &args, const complex &z)
    {
        complex_stack st;
        for(size_t i = 0; i < args.size(); i++) {
            if(m.find(args[i]) != m.end()) {
                m[args[i]](st);
            } else {
                if(args[i] == "z") {
                    st = st << z;
                } else {
                    st = st << complex(args[i]);
                }
            }
        }
        return +st;
    }
} 