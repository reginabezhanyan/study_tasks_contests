#include <stdio.h>
#include <stdlib.h> 
#include <vector>
#include <algorithm>
using namespace std;

struct edge{
    unsigned x, y, w; 
    edge(){}
    edge(unsigned a, unsigned b, unsigned c){
        x = a;
        y = b;
        w = c;
    }
};  
  

unsigned getColor(unsigned n, unsigned *nodes){
    if(n == nodes[n])
        return n;
    else 
        return getColor(nodes[n], nodes);
}


int main(){
   unsigned N, M = 0; 
   unsigned long long ans = 0;
   scanf ("%u", &N);
   vector<edge> graph;
   for(unsigned i = 0; i < N; i++) {
       for(unsigned j = 0; j < N; j++) {
           unsigned w;
           scanf("%u", &w);
           if(w != 0) {
               M++;
               edge k(i, j, w);
               graph.push_back(k);
           }
       } 
   }
   
   unsigned nodes[N]; 
   for(unsigned i = 0; i < N; i++) {
       nodes[i] = i; 
   }
   /*for(unsigned i = 0; i < M; i++) { 
       printf("%u -> %u = %u\n", graph[i].x, graph[i].y, graph[i].w); 
   }*/ 
   // Алгоритм Крускала

   // Сортируем все ребра в порядке возрастания весов
   sort(graph.begin(), graph.end(), [](const edge &a, const edge &b) { return a.w < b.w; }); 
   for(unsigned i = 0; i < M; i++){  
      unsigned u = getColor(graph[i].x, nodes);
      unsigned v = getColor(graph[i].y, nodes);
      if (u != v){  
         nodes[u] = nodes[v];
         ans += graph[i].w;
      }
   }
   printf("%llu\n", ans);
}