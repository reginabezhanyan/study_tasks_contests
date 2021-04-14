int
bitcount(STYPE value)
{
    UTYPE buf = value;
    int k = 0;
    while(buf) {
        k += buf & 1;
        buf >>= 1;
    }
    return k;
}