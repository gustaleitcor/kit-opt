#include "Data.h"
#include "ILS/ILS.h"
#include "MLP/MLP.h"
#include "Solution.h"
#include <bits/types/time_t.h>
#include <chrono>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {

  bool quiet = false;

  if (argc > 2 && std::string(argv[2]) == "-b") {
    quiet = true;
  }

  auto data = Data(argc, argv[1]);
  data.read();
  size_t n = data.getDimension();
  auto seed = time(NULL);
  srand(seed);

  auto file = ofstream("seed.txt");
  file << seed << std::endl;

  if (!quiet)
    std::cout << "Dimension: " << n << std::endl;
  // std::cout << "DistanceMatrix: " << std::endl;
  // data.printMatrixDist();
  auto start = chrono::high_resolution_clock::now();
  MLP::MLP(&data, quiet);
  auto stop = chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  std::cout << data.getInstanceName();
  printf(" - %lf\n", (double)(duration.count()));

  // MLP(&data);

  return 0;
}
