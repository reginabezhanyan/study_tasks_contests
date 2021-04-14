#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <unistd.h>

using namespace std;

// std::unique_ptr<T, Deleter>

int main()
{ 
    {
        FILE *f = fopen("a.txt", "w"); 
        std::unique_ptr<FILE, std::function<void (FILE *)>> ff{f, [](auto z) { fclose(z); }};
        fprintf(ff.get(), "!\n"); fflush(f);
        cout << sizeof(ff) << endl;
    }
    
    int a{2}, b{4};
    {
        FILE *f = fopen("a.txt", "w"); 
        auto deleter = [a, b](auto z) { fclose(z); printf("%d ", a); printf("%d", b);};
        cout << sizeof(deleter) << endl;
        std::unique_ptr<FILE, decltype(deleter)> ff{f, deleter};
        fprintf(ff.get(), "!\n"); fflush(f);
        cout << sizeof(ff) << endl;
    }
    
    getchar();
}