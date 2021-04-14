#include <stdint.h>
 
int32_t
satsum(int32_t v1, int32_t v2)
{
    uint32_t k = 0;
    int32_t res;
    if(!__builtin_sadd_overflow (v1,v2,&res)) {
        return res;
    } else {
        if(v1 > 0) {
            return ~k >> 1;
        } else {
            return (~k >> 1) + 1;
        }   
    }
}