#include "./moves.h"
#include "./utils.h"
#include "BuscaLocal.h"
#include "Construcao.h"
#include "Data.h"
#include "Pertubacao.h"
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

  std::cout << "Custo inicial: " << calcCost(solution.path, &data) << std::endl;

  Construcao(solution, &data);

  std::cout << "Custo após construção: " << solution.cost << std::endl;

  // printPath(path);
  while (bestImprovementSwap(solution, &data)) {
  };

  if (calcCost(solution.path, &data) != solution.cost) {
    std::cout << "lascou" << std::endl;
    std::cout << calcCost(solution.path, &data) << ' ' << solution.cost
              << std::endl;
  }

  std::cout << "Custo após swap: " << solution.cost << std::endl;

  return 0;

  for (int i = 0; i < 100; i++)
    BuscaLocal(solution, &data);

  // printPath(path);

  std::cout << "Custo após busca local: " << solution.cost << std::endl;

  return 0;

  std::cout << "Custo = " << solution.cost << std::endl;

  for (int i = 0; i < 1000; i++)
    Pertubacao(solution, &data);

  printPath(solution.path);

  std::cout << "Custo = " << solution.cost << std::endl;

  return 0;
}
