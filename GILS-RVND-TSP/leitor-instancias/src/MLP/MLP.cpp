#include "MLP.h"
#include "../Subsequence.h"
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <vector>

#define MAX_ITER 5
#define MAX_ITER_ILS 10

Solution MLP::MLP(Data *data) {
  size_t n = data->getDimension();
  std::vector<std::vector<Subsequence>> subseq_matrix(
      n, std::vector<Subsequence>(n));
  Solution solution(n);
  Solution bestOfAll;
  Solution best;

  Subsequence::updateAllSubseq(solution, subseq_matrix, data);

  bestOfAll.cost = solution.cost;

  std::cout << "Custo acumulado inicial: " << subseq_matrix[0][n - 1].C
            << std::endl;

  for (int i = 0; i < MAX_ITER; i++) {
    MLP::Construcao(solution, data);
    Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    best = solution;

    for (int iterIls = 0; iterIls < MAX_ITER_ILS; iterIls++) {
      MLP::BuscaLocal(solution, data, subseq_matrix);

      if (solution.cost < best.cost) {
        best = solution;
        iterIls = 0;
      }
      solution = MLP::Pertubacao(best, data, subseq_matrix);
      Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    }
    if (best.cost < bestOfAll.cost) {
      bestOfAll = best;
    }

    std::cout << "Solução acumulada parcial: " << bestOfAll.cost << std::endl;
  }

  bestOfAll.printPath(false);

  std::cout << "Custo acumulado final = " << bestOfAll.cost << std::endl;

  return bestOfAll;
}
