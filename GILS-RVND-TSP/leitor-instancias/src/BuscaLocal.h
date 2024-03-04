#pragma once

#include "./utils.h"
#include "Data.h"
#include "moves.h"
#include <random>
#include <vector>

inline void BuscaLocal(Solution &solution, Data *data) {

  vector<int> options = {1, 2, 3, 4, 5};
  bool improved = false;

  while (!options.empty()) {
    int n = rand() % options.size();
    switch (options[n]) {
    case 1:
      improved = bestImprovementSwap(solution, data);
      break;
    case 2:
      improved = bestImprovement2Opt(solution.path, data);
      break;
    case 3:
      improved = bestImprovementOrOpt(solution.path, data, 1);
      break;
    case 4:
      improved = bestImprovementOrOpt(solution.path, data, 2);
      break;
    case 5:
      improved = bestImprovementOrOpt(solution.path, data, 3);
      break;
    }

    if (improved) {
      options = {1, 2, 3, 4, 5};
    } else {
      options.erase(options.begin() + n);
    }
  }
}