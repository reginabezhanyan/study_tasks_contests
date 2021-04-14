#include <stdio.h> 
#include <string.h> 

void Simple_Merging_Sort (char *name){
    unsigned long long N, k, i, j;
    char *buf1 = new char[10002];
    char *buf2 = new char[10002]; 
    FILE *f, *f1, *f2;
    N = 2;  

    k = 1;
    while (k < N){
        f = fopen("input.txt","r");
        f1 = fopen("smsort_1.txt","w");
        f2 = fopen("smsort_2.txt","w"); 
        if(k == 1) N = 0;
        while (!feof(f)){ 
            for ( i = 0; i < k && (fgets(buf1, 10002, f) != NULL) ; i++ ){
                fputs(buf1, f1);
                if(k == 1) N++;
            }
            for (j = 0; j < k && (fgets(buf2, 10002, f) != NULL); j++ ){ 
                fputs(buf2, f2);
                if(k == 1) N++;
            }
        }
        //cout << N << endl;
        fclose(f2);
        fclose(f1);
        fclose(f);

        if((k * 2) < N) {
            f = fopen("input.txt","w");
        } else {
            f = fopen("output.txt","w");
        }
        f1 = fopen("smsort_1.txt","r");
        f2 = fopen("smsort_2.txt","r");
        fgets(buf1, 10002, f1);
        fgets(buf2, 10002, f2);
        while ( !feof(f1) && !feof(f2) ){
            i = 0;
            j = 0;
            while ( i < k && j < k && !feof(f1) && !feof(f2) ) { 
                if (strcmp(buf1, buf2) < 0) {
                    fputs(buf1, f);
                    fgets(buf1, 10002, f1);
                    i++;
                } else {
                    fputs(buf2, f);
                    fgets(buf2, 10002, f2);
                    j++;
                }
            }
            while (i < k && !feof(f1) ) {
                fputs(buf1, f);
                fgets(buf1, 10002, f1);
                i++;
            }
            while ( j < k && !feof(f2) ) {
                fputs(buf2, f);
                fgets(buf2, 10002, f2);
                j++;
            }
        }
        
        while ( !feof(f1) ) {
            fputs(buf1, f);
            fgets(buf1, 10002, f1);
        }
        while ( !feof(f2) ) {
            fputs(buf2, f);
            fgets(buf2, 10002, f2);
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