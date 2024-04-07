#include "./ILS/ILS.h"
#include "./Subsequence.h"
#include "Data.h"
#include "MLP/MLP.h"
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char **argv) {

  auto data = Data(argc, argv[1]);
  data.read();
  size_t n = data.getDimension();
  srand(time(NULL));

  std::cout << "Dimension: " << n << std::endl;
  // std::cout << "DistanceMatrix: " << std::endl;
  // data.printMatrixDist();

  MLP::MLP(&data);

  // MLP(&data);

  return 0;
}
