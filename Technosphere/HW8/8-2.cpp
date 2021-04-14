#include <stdio.h> 
#include <vector>
#include <iostream> 
#include<algorithm>
#include <queue>

using namespace std;

unsigned N;
pair<unsigned, unsigned> res;  
vector<vector<unsigned>> used, d; //вектор посещений, 1 - вершина посещена 
vector<vector<pair<unsigned, unsigned>>> p;
vector<pair<unsigned, unsigned>> a;

void bfs(pair<unsigned, unsigned> s) {
    queue<pair<unsigned, unsigned>> Q; //очередь вершин
    Q.push(s);  
    used[s.first][s.second] = true; 
    p[s.first][s.second].first = -1; 
    p[s.first][s.second].second = -1; 
    unsigned size = 8; 
    while(!Q.empty()) {
        pair<unsigned, unsigned> v = Q.front();
        Q.pop();
        for(unsigned i = 0; i < size; i++) {
            pair<unsigned, unsigned> to = v;
            to.first += a[i].first;
            to.second += a[i].second;
            if(to.first >= 0 && to.first < N && to.second >= 0 && to.second < N && !used[to.first][to.second]) {
                used[to.first][to.second] = true;
                Q.push(to);
                d[to.first][to.second] = d[v.first][v.second] + 1;
                p[to.first][to.second] = v;
            }
            if(used[res.first][res.second]) {
                return;     
            }
        }
    }
}

int main() {
    scanf("%u", &N);
    pair<unsigned, unsigned> s1;
    char tmp;
    cin >> tmp >> s1.second;
    s1.first = tmp - 'A';
    s1.second -= 1; 
    cin >> tmp >> res.second;
    res.first = tmp - 'A';
    res.second -= 1; 
    used.resize(N); 
    p.resize(N); 
    d.resize(N);
    for(unsigned i = 0; i < N; i++) {
        used[i].resize(N);
        p[i].resize(N); 
        d[i].resize(N);
    } 
    
    a.push_back(make_pair(1, 2));
    a.push_back(make_pair(-1, 2));
    a.push_back(make_pair(2, 1));
    a.push_back(make_pair(2, -1));
    a.push_back(make_pair(1, -2));
    a.push_back(make_pair(-1, -2));
    a.push_back(make_pair(-2, 1));
    a.push_back(make_pair(-2, -1)); 
    
    bfs(s1); 
    
    vector<pair<unsigned, unsigned>> path;
    pair<unsigned, unsigned> null;
    null.first = -1; null.second = -1;
    for(pair<unsigned, unsigned> v = res; v != null; v = p[v.first][v.second]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    unsigned size = path.size();
    cout << size - 1 << endl;
    for(unsigned i = 1; i < size; i++) {
        printf("%c%d\n", 'A' + path[i].first, path[i].second + 1); 
    }
    printf("\n");
}