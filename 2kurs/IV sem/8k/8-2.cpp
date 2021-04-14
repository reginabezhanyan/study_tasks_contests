#include <iostream>
#include <cctype>

void scan(void) {
    char tmp;
    tmp = getchar();
    while(!isspace(tmp)) { 
        if((tmp = getchar()) == EOF)
            break;
    }
    std::cout << false << std::endl;
}

int main()
{
    unsigned long long k, m, n, kt, mt;
    char tmp; 
    bool fl = false;
    
    while(1) {
        if(!fl) {
            m = 0; k = 0; n = 0;
            kt = 0; mt = 0;
        }
        if((tmp = getchar()) == EOF) {
            if(fl) {
                if((kt == 0) && (mt == 0) && (k != 0) && (m != 0)) {
                    std::cout << true << std::endl; 
                } else {
                    std::cout << false << std::endl;
                } 
            }
            break;
        }
        if(isspace(tmp)) { 
            if(fl) {
                if((kt == 0) && (mt == 0) && (k != 0) && (m != 0)) {
                    std::cout << true << std::endl;
                } else {
                    std::cout << false << std::endl;
                }
                fl = false;
                m = 0; k = 0; n = 0;
                kt = 0; mt = 0;
            }
        } else if ((tmp == '0') || (tmp == '1')){
            if(n == 0) { 
                fl = true;
                if(tmp == '0') {
                    if(m != 0) {
                        n++;
                    } else {
                        k++;
                    }
                } else if(tmp == '1') {
                    if(k == 0) {
                        fl = false;
                        scan();
                    } else {
                        m++;
                    }
                }
            } 
            if(n > 0) { 
                if(tmp == '0') { 
                    kt++;
                    if(kt > k) {
                        fl = false;
                        scan();
                    }
                } else if(tmp == '1') {
                    if(kt == k) {
                        mt++;
                        if(mt > m) { 
                            fl = false;
                            scan();
                        }
                    } else { 
                        fl = false;
                        scan();
                    }
                }
            
                if((kt == k) && (mt == m)) { 
                    kt = 0;
                    mt = 0;
                }
            }
        } else {
            fl = false;
            scan();  
        }
    }
}