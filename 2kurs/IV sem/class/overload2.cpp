void f(int a, int b); // {}
void f(double a, double b); // {}

int main()
{
    int vi;
    long vl;
    double vd;
    
    f(vi,vl); //по 1 арг приоритет
    /*  f(int, int) : { 0, 1}
        f(double, double) : { 1, 1}
    */
    f(vd, vl);
    
    f(vd, vi);
    /*  вектора не сравнимы
        f(int, int) : { 1, 0} 
        f(double, double) : { 0, 1}
    */
    f(vl, vl);
    /*  вектора не сравнимы
        f(int, int) : { 1, 1}
        f(double, double) : { 1, 1}
    */
    
    f(vl, vi);
    f(vl, vd);
}