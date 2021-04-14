#include <iostream>
#include <ctime>



int main() {
    int N = 1000000;
    auto start = clock();
    unsigned *p;
for (int i = 0; i < N; i++) {
  p = (unsigned*)malloc(60000000);
  free(p);
}
auto end = clock();

std::cout << "malloc[] + free[]: " << (double)(end - start) / ((double) CLOCKS_PER_SEC) << std::endl;

start = clock();
for (int i = 0; i < N; i++) {
  p = new unsigned [60000000];
  delete[] p;
}
end = clock();

std::cout << "new[] + delete[]: " << (double)(end - start) / ((double) CLOCKS_PER_SEC) << std::endl;
}
