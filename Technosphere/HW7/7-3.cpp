#include <stdio.h> 
#include <vector>
#include <iostream> 

using namespace std;

int main() {
    unsigned M, N;
    cin >> N >> M;
    vector<vector<unsigned>> graph, road;
    vector<vector<bool>> used;
    graph.resize(N);
    road.resize(N);
    used.resize(N);
    unsigned a[4][2];
    a[0][0] = 0; a[0][1] = 1;
    a[1][0] = 0; a[1][1] = -1;
    a[2][0] = -1; a[2][1] = 0;
    a[3][0] = 1; a[3][1] = 0;
    for(unsigned i = 0; i < N; i++) {
        graph[i].resize(M);
        road[i].resize(M);
        used[i].resize(M);
        for(unsigned j = 0; j < M; j++) {
            scanf("%u", &graph[i][j]);
            road[i][j] = 1001;
            used[i][j] = false; 
        }
        
    }
    road[0][0] = 0;
    //алгоритм Дейкстры
    unsigned mini, minj;
    unsigned min;
    do {
        mini = N;
        minj = M;
        min = 1001;
        for(unsigned i =0; i < N; i++) {
            for(unsigned j = 0; j < M; j++) {
                if(!used[i][j] && road[i][j] < min) {
                    min = road[i][j];
                    mini = i;
                    minj = j;
                }
            }
        } 
        if (mini != N) {
            for(unsigned i =0; i < 4; i++) { 
                unsigned k = mini + a[i][0];
                unsigned l = minj + a[i][1];
                if(k < N && l < M && !used[k][l]) {
                    if(graph[k][l] < graph[mini][minj]) {
                        if(road[mini][minj] < road[k][l]) road[k][l] = road[mini][minj];
                    } else {
                        unsigned tmp = graph[k][l] - graph[mini][minj] + road[mini][minj];
                        //printf("k l: %d %d tmp: %d\n", k, l, tmp);
                        if(tmp < road[k][l]) road[k][l] = tmp;
                    }
                }
            } 
            used[mini][minj] = true;
        } 
    } while (mini < N);
    
    printf("%d\n", road[N - 1][M - 1]);
}