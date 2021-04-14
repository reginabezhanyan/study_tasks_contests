#include <iostream> 
#include <float.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>  

using namespace std;  

struct Point { 
    double x, y; 
};  
 
double compareX(const void* a, const void* b) { 
    Point *p1 = (Point *)a,  *p2 = (Point *)b; 
    return (p1->x - p2->x); 
} 

double compareY(const void* a, const void* b) { 
    Point *p1 = (Point *)a,   *p2 = (Point *)b; 
    return (p1->y - p2->y); 
} 
  
  
double dist(Point p1, Point p2) { 
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + 
                 (p1.y - p2.y)*(p1.y - p2.y) 
               ); 
} 
  
double bruteForce(Point P[], int n) { 
    double min = DBL_MAX; 
    for (int i = 0; i < n; ++i) 
        for (int j = i+1; j < n; ++j) 
            if (dist(P[i], P[j]) < min) 
                min = dist(P[i], P[j]); 
    return min; 
} 
  
double min(double x, double y) { 
    return (x < y)? x : y; 
} 
  
 
double stripClosest(Point strip[], int size, float d) { 
    double min = d;  // Initialize the minimum distance as d 
  
    for (int i = 0; i < size; ++i) 
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) 
            if (dist(strip[i],strip[j]) < min) 
                min = dist(strip[i], strip[j]); 
  
    return min; 
} 

int main() {
    unsigned N;
    scanf("%u", &N);
    Point *Px = new Point[N];
    Point *Py = new Point[N];
    
    for(unsigned i = 0; i < N; i++) {
        scanf("%lf%lf", &Px[i].x, &Px[i].y);
        Py[i].x = Px[i].x;
        Py[i].y = Px[i].y;
    }
    
    qsort (Px, N, sizeof(double), compareX);
    qsort (Py, N, sizeof(double), compareY);
}