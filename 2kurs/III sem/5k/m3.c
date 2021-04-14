void
normalize_path(char *buf)
{
    char *tmp = buf;
    char up = *tmp;
    buf++;
    tmp++;
    while(*tmp) { 
        if(*tmp == '/' && up == '/') {
            while(*tmp == '/') {
                tmp++;
            }
        }
        *buf = *tmp;
        up = *tmp;
        buf++;
        tmp++;  
    }
    *buf = '\0';
}