
struct Int
{
    int v_{};
    
    Int(int v) : v_{v} {}
    
    /*Int operator+(const Int &v2) const 
    {
        return v_ + v2.v_; // Int(int) -> Int(const Int &): Int(int)
        //return value optimizatoin: Int(int)
    }*/
};

Int operator *(const Int &v1, const Int &v1)
{
    return v1.v_ * v2.v_;
}

Int operator -(const Int &v)
{
    return { -v.v_ };
}

Int operator ++(Int &v, int a) //постфиксная
{
    Int t{v};
    ++v.v;
    return t;
}

//const нужен, чтобы не допускать -- -- -- x
const Int &operator--(Int &v) //префиксный
{
    --v.v;
    return v;
}

int main()
{
    Int a, b, c;
    //Int b ---- a; от четности '-' зависит ответ
    Int d = (a++ + --b) * -c; //компилятор преобразует в функциональную запись:
 
    Int e = operator*((operator++(a,0)).operator+(operator--(b))), operator-(c));
}
//тернарные операции перегружать нельзя, ., ::, ?
/* TODO: =, +=, *= ...
   ->, [], ()
   <=>, 