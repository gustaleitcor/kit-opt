#include "MLP.h"
#include "../ILS/ILS.h"
#include "../Subsequence.h"
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <vector>

#define MAX_ITER 10
#define MAX_ITER_ILS 100

Solution MLP::MLP(Data *data, bool quiet) {
  size_t n = data->getDimension();

  std::vector<std::vector<Subsequence>> subseq_matrix(
      n + 1, std::vector<Subsequence>(n + 1));

  Solution solution(n);
  Solution bestOfAll;
  Solution best;

  Subsequence::updateAllSubseq(solution, subseq_matrix, data);

  solution.printSolution();

  bestOfAll.cost = solution.cost;
  if (!quiet)
    std::cout << "Custo acumulado inicial: " << subseq_matrix[0][n - 1].C
              << std::endl;

  for (int counterIls = 0; counterIls < MAX_ITER; counterIls++) {
    MLP::Construcao(solution, data);
    Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    best = solution;

    // std::cout << "counterIls: " << counterIls << std::endl;

    for (int iterIls = 0; iterIls < MAX_ITER_ILS; iterIls++) {
      MLP::BuscaLocal(solution, data, subseq_matrix);
      // std::cout << "iterIls: " << iterIls << std::endl;

      if (solution.cost < best.cost) {
        best = solution;
        iterIls = 0;
      }
      solution = MLP::Pertubacao(best, data);
      Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    }
    if (best.cost < bestOfAll.cost) {
      bestOfAll = best;
    }

    if (!quiet)
      std::cout << "Solução acumulada parcial: " << bestOfAll.cost << std::endl;
  }

  if (!quiet) {
    bestOfAll.printSolution();
    Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    std::cout << "Custo acumulado final = " << bestOfAll.cost << std::endl;
    std::cout << "Custo final = "
              << Solution::calcCost(bestOfAll.sequence, data) << std::endl;
  }
  std::cout << "Custo acumulado final = " << bestOfAll.cost << std::endl;

  return bestOfAll;
}
