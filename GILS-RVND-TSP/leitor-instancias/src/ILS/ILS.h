#pragma once
#include "../Data.h"
#include "Construction.h"
#include "LocalSearch.h"
#include "Pertubation.h"
#include "utils.h"
#include <climits>
#include <cmath>
#include <cstdlib>

#define MAX_ITER 5
#define MAX_ITER_ILS 1000

inline Solution ILS(Solution &solution, Data *data) {
  Solution bestOfAll;
  bestOfAll.cost = solution.cost;
  Solution best;

  for (int i = 0; i < MAX_ITER; i++) {
    Construcao(solution, data);
    best = solution;

    for (int iterIls = 0; iterIls < MAX_ITER_ILS; iterIls++) {
      BuscaLocal(solution, data);
      if (solution.cost < best.cost) {
        best = solution;
        iterIls = 0;
      }
      solution = Pertubacao(best, data);
    }
    if (best.cost < bestOfAll.cost) {
      bestOfAll = best;
    }

    std::cout << "Solução parcial: " << bestOfAll.cost << std::endl;
  }

  return bestOfAll;
}