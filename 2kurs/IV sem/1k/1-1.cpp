class Sum
{
    int a = 0, b = 0;
    
public: 
    Sum(int a_, int b_) : a{a_}, b{b_}
    { 
    }
    Sum(Sum v, int b_) : a{v.get()}, b{b_}
    {
    }
    Sum(int a_, Sum v) : a{a_}, b{v.get()}
    { 
    }
    
    int get() const { return a + b; }; 
}; 