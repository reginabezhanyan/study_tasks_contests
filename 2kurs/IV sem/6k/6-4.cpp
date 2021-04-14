#include <iostream>

/*class Pimpl
{
    private:
        char *str;
};

class String
{
    Pimpl *str;
    public:
        operator
}*/

class Pimpl
{
    public:
        explicit Pimpl();
        ~Pimpl(); 
 
    private:
        char *str;
};

class String
{
    Pimpl *pimpl;
    
    public:
        
};

int main()
{
    String a = "abc";
    //String b = a; // в памяти хранится "abc" в одном экземпляре 
    //c = a; 
    //b += "aaa"; // для b создался новый "массив" символов.
    //c[1] = 'f'; // a не изменилось 
    //std::cout << string(c);
}


