#include "../Subsequence.h"
#include "MLP.h"
#include <algorithm>
#include <cstddef>

typedef struct SwapInfo_t {
  size_t i, j;
  double delta;
} SwapInfo;

bool MLP::bestImprovementSwap(
    Solution &solution, Data *data,
    std::vector<std::vector<Subsequence>> &subseq_matrix) {
  size_t n = data->getDimension();
  Subsequence subsequence;
  SwapInfo bestSwap = (SwapInfo){.i = 0, .j = 0, .delta = 0};
  double delta = 0;

  for (int i = 1; i < n - 1; i++) {
    for (int j = i + 2; j < n - 1; j++) {
      subsequence = Subsequence::concatenate(subseq_matrix[0][i - 1],
                                             subseq_matrix[j][j], data)
                        .concatenate(subseq_matrix[i + 1][j - 1], data)
                        .concatenate(subseq_matrix[i][i], data)
                        .concatenate(subseq_matrix[j + 1][n - 1], data);

      delta = subsequence.C - subseq_matrix[0][n - 1].C;

      if (delta < bestSwap.delta) {
        bestSwap.i = i;
        bestSwap.j = j;
        bestSwap.delta = delta;
      }
    }
  }

  if (bestSwap.delta < 0) {
    Solution::swap(solution.path, bestSwap.i, bestSwap.j);
    Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    return true;
  }

  return false;
}

typedef struct Info2opt {
  size_t i, j;
  double delta;
} Info2opt_t;

bool MLP::bestImprovement2Opt(
    Solution &solution, Data *data,
    std::vector<std::vector<Subsequence>> &subseq_matrix) {
  size_t n = data->getDimension();
  Subsequence subsequence;
  Info2opt best2opt = (Info2opt){.i = 0, .j = 0, .delta = 0};
  double delta = 0;

  for (int i = 1; i < n - 1; i++)
    for (int j = i + 2; j < n - 1; j++) {
      subsequence = Subsequence::concatenate(subseq_matrix[0][i - 1],
                                             subseq_matrix[j][i], data)
                        .concatenate(subseq_matrix[j + 1][n - 1], data);

      delta = subsequence.C - subseq_matrix[0][n - 1].C;

      if (delta < best2opt.delta) {
        best2opt.i = i;
        best2opt.j = j;
        best2opt.delta = delta;
      }
    }

  if (best2opt.delta < 0) {
    reverse(solution.path.begin() + best2opt.i,
            solution.path.begin() + best2opt.j + 1);
    Subsequence::updateAllSubseq(solution, subseq_matrix, data);
    return true;
  }

  return false;
}

typedef struct OrOptInfo {
  size_t i, j;
  double delta;
} OrOptInfo_t;

bool MLP::bestImprovementOrOpt(
    Solution &solution, Data *data,
    std::vector<std::vector<Subsequence>> &subseq_matrix, int n) {

  Subsequence subsequence;
  OrOptInfo bestOrOp = (OrOptInfo){.i = 0, .j = 0, .delta = 0};
  size_t aux, size = solution.path.size();
  double delta = 0;

  for (size_t i = 1; i < size - n; i++) {
    for (size_t j = 1; j < size - 1; j++) {

      if (j >= i - 1 && j < i + n)
        continue;

      if (j < i) {
        subsequence =
            Subsequence::concatenate(subseq_matrix[0][j - 1],
                                     subseq_matrix[i][i + n - 1], data)
                .concatenate(subseq_matrix[j][i - 1], data)
                .concatenate(subseq_matrix[i + n][size - 1], data);

        delta = subsequence.C - subseq_matrix[0][size - 1].C;

        if (delta < bestOrOp.delta) {
          bestOrOp.i = i;
          bestOrOp.j = j - 1;
          bestOrOp.delta = delta;
        }

      } else {
        subsequence = Subsequence::concatenate(subseq_matrix[0][i - 1],
                                               subseq_matrix[i + n][j], data)
                          .concatenate(subseq_matrix[i][i + n - 1], data)
                          .concatenate(subseq_matrix[j + 1][size - 1], data);

        delta = subsequence.C - subseq_matrix[0][size - 1].C;

        if (delta < bestOrOp.delta) {
          bestOrOp.i = i;
          bestOrOp.j = j;
          bestOrOp.delta = delta;
        }
      }
    }
  }

  if (bestOrOp.delta < 0) {
    if (bestOrOp.i > bestOrOp.j) {
      for (int i = 0; i < n; i++) {
        aux = solution.path[bestOrOp.i + i];
        solution.path.erase(solution.path.begin() + bestOrOp.i + i);
        solution.path.insert(solution.path.begin() + bestOrOp.j + i + 1, aux);
      }
    } else {
      for (int i = 0; i < n; i++) {
        aux = solution.path[bestOrOp.i];
        solution.path.erase(solution.path.begin() + bestOrOp.i);
        solution.path.insert(solution.path.begin() + bestOrOp.j, aux);
      }
    }

    Subsequence::updateAllSubseq(solution, subseq_matrix, data);

    return true;
  }

  return false;
}