#include "../parser/Data.h"
#include "MLP.h"
#include <bits/types/time_t.h>
#include <chrono>
#include <iostream>

int main(int argc, char **argv) {

  auto data = Data(argc, argv[1]);
  data.read();
  size_t n = data.getDimension();
  srand(time(NULL));

  auto start = chrono::high_resolution_clock::now();
  MLP::MLP(&data);
  auto stop = chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  std::cout << data.getInstanceName();
  printf(" - %lf\n", (double)(duration.count()));

  return 0;
}