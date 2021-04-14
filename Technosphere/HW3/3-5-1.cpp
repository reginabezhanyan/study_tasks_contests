#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

void sort_bub(char **a, int n) { 
   bool sorted = false; 
   char *tmp = new char[10001];
   while (!sorted) {
      sorted = true;
      for (int i = 0; i < n-1; i++) { 
        if (strcmp(a[i+1],a[i]) < 0) {
           strcpy(tmp, a[i]);
           strcpy(a[i], a[i+1]);
           strcpy(a[i+1], tmp); 
           sorted = false;
        }
      }
    }
    delete []tmp;
}

void Simple_Merging_Sort (char *name){
    unsigned long long N, k, i, j;
    char *buf1 = new char[10001];
    char *buf2 = new char[10001]; 
    char **buf = new char*[8];
    FILE *f, *f1, *f2;
    N = 0;  
    k = 8;
    for(int g = 0; g < 8; g++) { 
        buf[g] = new char[10001];
    }
    
    f = fopen(name,"r");
    f1 = fopen("smsort_1.txt","w");
    f2 = fopen("smsort_2.txt","w"); 
    while (!feof(f)){ 
        for ( i = 0; i < k && (fgets(buf[i], 10001, f) != NULL) ; i++ ){  
            N++;
        } 
        unsigned long long L1 = min(N, k); 
        sort_bub(buf, L1);
        for(unsigned long long g = 0; g < L1; g++) {
            fputs(buf[g], f1);
        } 
        for (j = 0; j < k && (fgets(buf[i], 10001, f) != NULL); j++ ){  
            N++;
        }
        unsigned long long L2 = min(N - L1, k);
        sort_bub(buf, L2);
        for(unsigned long long g = 0; g < L2; g++) {
            fputs(buf[g], f2);
        }
    } 
    
    fclose(f2);
    fclose(f1);
    fclose(f);
    
    if((k * 2) < N) {
        f = fopen(name,"w");
    } else {
         f = fopen("output.txt","w");
    }
    f1 = fopen("smsort_1.txt","r");
    f2 = fopen("smsort_2.txt","r");
    fgets(buf1, 10001, f1);
    fgets(buf2, 10001, f2);
    while ( !feof(f1) && !feof(f2) ){
        i = 0;
        j = 0;
        while ( i < k && j < k && !feof(f1) && !feof(f2) ) { 
            if (strcmp(buf1, buf2) < 0) {
                fputs(buf1, f);
                fgets(buf1, 10001, f1);
                i++;
            } else {
                fputs(buf2, f);
                fgets(buf2, 10001, f2);
                j++;
            }
        }
        while (i < k && !feof(f1) ) {
            fputs(buf1, f);
            fgets(buf1, 10001, f1);
            i++;
        }
        while ( j < k && !feof(f2) ) {
            fputs(buf2, f);
            fgets(buf2, 10001, f2);
            j++;
        }
    }
        
    while ( !feof(f1) ) {
       fputs(buf1, f);
       fgets(buf1, 10001, f1);
    }
    while ( !feof(f2) ) {
        fputs(buf2, f);
        fgets(buf2, 10001, f2);
    }
    fclose(f2);
    fclose(f1);
    fclose(f);
    
    k = 16;
    while (k < N){
        f = fopen(name,"r");
        f1 = fopen("smsort_1.txt","w");
        f2 = fopen("smsort_2.txt","w"); 
        if(k == 1) N = 0;
        while (!feof(f)){ 
            for ( i = 0; i < k && (fgets(buf1, 10001, f) != NULL) ; i++ ){
                fputs(buf1, f1);
                if(k == 1) N++;
            }
            for (j = 0; j < k && (fgets(buf2, 10001, f) != NULL); j++ ){ 
                fputs(buf2, f2);
                if(k == 1) N++;
            }
        }
        //cout << N << endl;
        fclose(f2);
        fclose(f1);
        fclose(f);

        if((k * 2) < N) {
            f = fopen(name,"w");
        } else {
            f = fopen("output.txt","w");
        }
        f1 = fopen("smsort_1.txt","r");
        f2 = fopen("smsort_2.txt","r");
        fgets(buf1, 10001, f1);
        fgets(buf2, 10001, f2);
        while ( !feof(f1) && !feof(f2) ){
            i = 0;
            j = 0;
            while ( i < k && j < k && !feof(f1) && !feof(f2) ) { 
                if (strcmp(buf1, buf2) < 0) {
                    fputs(buf1, f);
                    fgets(buf1, 10001, f1);
                    i++;
                } else {
                    fputs(buf2, f);
                    fgets(buf2, 10001, f2);
                    j++;
                }
            }
            while (i < k && !feof(f1) ) {
                fputs(buf1, f);
                fgets(buf1, 10001, f1);
                i++;
            }
            while ( j < k && !feof(f2) ) {
                fputs(buf2, f);
                fgets(buf2, 10001, f2);
                j++;
            }
        }
        
        while ( !feof(f1) ) {
            fputs(buf1, f);
            fgets(buf1, 10001, f1);
        }
        while ( !feof(f2) ) {
            fputs(buf2, f);
            fgets(buf2, 10001, f2);
        }
        fclose(f2);
        fclose(f1);
        fclose(f);
        k *= 2; 
        
    }
    remove("smsort_1.txt");
    remove("smsort_2.txt");
}

int main() {
    char name[] = "input.txt";
    Simple_Merging_Sort(name); 
}