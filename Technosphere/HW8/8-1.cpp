#include <stdio.h> 
#include <vector>
#include <iostream>

using namespace std;

vector<vector<unsigned>> graph;
vector<unsigned> color;
string ans;

void dfs(unsigned col, unsigned id, vector<bool> &used) {
    unsigned size = graph[id].size();
    //printf("col: %d \n", col);
    if(color[id] != 0 && color[id] != col) {
        //printf("dfs NO\n");
        ans = "NO"; 
        return;
    } 
    color[id] = col;
    used[id] = true;
    
    for(unsigned j = 0; j < size; j++) {
        if(!used[graph[id][j]]) {
            used[graph[id][j]] = true;
            //printf("%d -> %d\n", id, graph[id][j]);
            //printf("color %d -> %d\n", color[id], color[graph[id][j]]);
            dfs((col & 1) + 1, graph[id][j], used);
            used[graph[id][j]] = false;
        }
    } 
}

int main() {
    unsigned N, M;
    scanf("%u%u", &N, &M); 
    //вершина цвета 0 - не расскрашена, 1 -  1й цвет, 2 - 21 цвет
    graph.resize(N); 
    unsigned v1, v2;
    for(unsigned i = 0; i < M; i++) {
        scanf("%u%u", &v1, &v2); 
        graph[v1].push_back(v2); 
        graph[v2].push_back(v1); 
    }
    ans = "YES";
    vector<bool> used;
    used.resize(N);
    color.resize(N);
    dfs(1, 0, used);
    cout << ans << endl;
    /*for(unsigned i = 0; i < N; i++) {
        for(unsigned j = 0; j < graph[i].size(); j++) {
            printf("(%d)  ", graph[i][j]);
        }
        printf("\n");
    }*/
}