#include "Data.h"
#include "ILS/ILS.h"
#include "MLP/MLP.h"
#include <iostream>

int main(int argc, char **argv) {

  bool quiet = false;

  if (argc > 2 && std::string(argv[2]) == "-b") {
    quiet = true;
  }

  auto data = Data(argc, argv[1]);
  data.read();
  size_t n = data.getDimension();
  srand(time(NULL));

  if (!quiet)
    std::cout << "Dimension: " << n << std::endl;
  // std::cout << "DistanceMatrix: " << std::endl;
  // data.printMatrixDist();

  MLP::MLP(&data, true);

  // MLP(&data);

  return 0;
}
