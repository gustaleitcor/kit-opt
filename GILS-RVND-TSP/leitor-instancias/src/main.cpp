#include "./utils.h"
#include "BuscaLocal.h"
#include "Data.h"
#include "ILS.h"
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

  Solution solution = (Solution){.path = vector<int>(n), .cost = 0};

  std::iota(solution.path.begin(), solution.path.end(), 1);
  solution.cost = calcCost(solution.path, &data);

  solution = ILS(solution, &data);

  printPath(solution.path, false);

  std::cout << "Custo final = " << solution.cost << std::endl;

  return 0;
}
