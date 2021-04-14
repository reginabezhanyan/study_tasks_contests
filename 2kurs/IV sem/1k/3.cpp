class Sub
{
    int a = 0, b = 0;
    
public: 
    Sub(int a_, int b_) : a{a_}, b{b_}
    { 
    }
    Sub(Sub v, int b_) : a{v.value()}, b{b_}
    {
    } 
    Sub(int a_, Sub v) : a{a_}, b{v.value()}
    {
    } 
     
    int value() const { return a - b; }; 
}; 