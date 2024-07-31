#include "./MLP.h"

void MLP::BuscaLocal(Solution &solution, Data *data,
                     std::vector<std::vector<Subsequence>> &subseq_matrix) {

  vector<int> options = {1, 2, 3, 4, 5};
  bool improved = false;

  while (!options.empty()) {
    int n = rand() % options.size();
    switch (options[n]) {
    case 1:
      improved = MLP::bestImprovementSwap(solution, data, subseq_matrix);
      break;
    case 2:
      improved = MLP::bestImprovement2Opt(solution, data, subseq_matrix);
      break;
    case 3:
      improved = MLP::bestImprovementOrOpt(solution, data, subseq_matrix, 1);
      break;
    case 4:
      improved = MLP::bestImprovementOrOpt(solution, data, subseq_matrix, 2);
      break;
    case 5:
      improved = MLP::bestImprovementOrOpt(solution, data, subseq_matrix, 3);
      break;
    }

    if (improved) {
      options = {1, 2, 3, 4, 5};
      improved = false;
    } else {
      options.erase(options.begin() + n);
    }
  }
}