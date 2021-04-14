#include <stdio.h> 
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

#define NMax 2000
using namespace std;

void print(vector<bitset<NMax>> graph, unsigned N) {
    for (unsigned k = 0; k < N; ++k){
        for(int i = N - 1; i >= 0; i--){
            cout << graph[k][i];
        }
        printf("\n");
    }
}

int main() {
    unsigned N;
    cin >> N;
    vector<bitset<NMax>> graph; 
    char input[NMax + 2]; 
    for(unsigned i = 0; i < N; i++){ 
        scanf("%s", input);   
        bitset<NMax> bset(input);
        graph.push_back(bset);
    }
    
    //Алгоритм Флойда-Уоршелла
    for (int k1 = 0, k2 = N - 1; k1 < N; k1++, k2--) {
        for (int i = 0; i < N; i++) {
            if(graph[i][k2]) {
                 graph[i] = graph[i] | graph[k1]; 
            }
        }
    } 
    print(graph, N);
}


