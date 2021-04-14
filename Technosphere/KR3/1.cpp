#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check (int begin, int end, char* str) {
	char c = str[begin];
	for (int i = 0; i <= end; i++){
		if (str[begin + i] != c) return false;
	}
	return true;
}
long long poww (int a) {
	long long res = 1;
	for (int i = 0; i < a; i++) {
		res = res*2;
	}
	return res;	
}
long long f (int beg, int end, char* str) {
	if (beg == end) return 1;
	if (beg > end) return 0;
    
	if (check(beg, end, str)) {
        return poww(end - beg + 1)-1;
    }
		
	long long sum = 0;
	for (int j = beg; j < end; j++) {
		if (str[j] == str[end]) sum += f (j+1, end-1, str) + 1;
	}
	return f(beg, end-1, str) + sum + 1;
}
int main () {
	char str[31];
	int size;
	long long res;
	scanf ("%s", str); 
	res = f(0, strlen(str) - 1, str);
	printf ("%lld\n", res);
	return 0;
}