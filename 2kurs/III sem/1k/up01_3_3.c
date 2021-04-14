#include <stdio.h>
#include <stdlib.h>

struct Pair
{
    int key;
    int value;
};

void MergeSort(struct Pair *data, struct Pair *tmp, size_t l, size_t r);
void merge(struct Pair *data, struct Pair *tmp, size_t l, size_t r, size_t m);

void
process(struct Pair *data, size_t size){
    if(size <= 0){
        return;
    }
    size_t l = 0;
    size_t r = size - 1;
    struct Pair *tmp = calloc(size / 2 + 1, sizeof(*tmp)); //буфер
    if (tmp == NULL){
        exit(1);
    }
    MergeSort(data, tmp, l, r);
    free(tmp);
}

void
MergeSort(struct Pair *data, struct Pair *tmp, size_t l, size_t r)
{
    if (l >= r) {
        return;
    }
    size_t m = (l + r) / 2;
    MergeSort(data, tmp, l, m);
    MergeSort(data, tmp, m  + 1, r);
    merge(data, tmp, l, r, m);
}

void
merge(struct Pair *data, struct Pair *tmp, size_t l, size_t r, size_t m)
{
    if (l >= r || m < l || m > r){
        return; 
    }
    for(size_t i = l; i <= m; i++){
        tmp[i - l] = data[i];
    }
    for (size_t i = l, j = 0, k = m + 1; i <= r; ++i) {   
        if (j > m - l) {      
            data[i] = data[k++];
        } else if(k > r) {
            data[i] = tmp[j++];
        } else {
            if (tmp[j].key > data[k].key) {
                data[i] = data[k++];
            } else {
                data[i] = tmp[j++];
            }
        } 
    }
}