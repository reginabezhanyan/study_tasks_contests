#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pair
{
    int key;
    int value;
};

int compar
(const void *p1, const void *p2, void *ind)
{
	if(p1.key == p2.key){
		return ind
	}
}

void
process(struct Pair *data, size_t size){
	int *ind = malloc(size*sizeof(*ind));
	for(int i = 0; i < size; i++){
	    ind[i] = i;
	}
	void qsort_r(data, size, sizeof(struct Pair), compar, ind);
	 
}

 
int
main(void)
{
    int n = 100, tmp[100] = {};
	struct Pair data[100];
	for(int i = 0; i < n; i++){
		data[i].key = rand() % 100;
		tmp[data[i].key] ++;
	    data[i].value = tmp[data[i].key];
    }
	for(int i = 0; i < n; i++){
		printf("%d) %d %d\n", i, data[i].key, data[i].value);
    }
    return 0;
}