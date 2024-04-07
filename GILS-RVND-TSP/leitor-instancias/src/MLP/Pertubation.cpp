#include "../Subsequence.h"
#include "MLP.h"
#include <algorithm>

struct slice {
  size_t index;
  size_t size;
};

Solution MLP::Pertubacao(Solution solution, Data *data,
                         std::vector<std::vector<Subsequence>> &subseq_matrix) {

  struct slice sliceA;
  struct slice sliceB;

  if (solution.path.size() < 30)
    sliceA.size = 2;
  else
    sliceA.size = ceil(rand() % (solution.path.size() / 10 - 2)) + 2;

  sliceA.index = rand() % (solution.path.size() - sliceA.size + 1);

  std::rotate(solution.path.begin(), solution.path.begin() + sliceA.index,
              solution.path.end());

  if (solution.path.size() < 30)
    sliceB.size = 2;
  else
    sliceB.size =
        ceil(rand() % ((solution.path.size() - sliceA.size) / 10 - 2)) + 2;

  sliceB.index =
      rand() % (solution.path.size() - sliceA.size - sliceB.size + 1) +
      sliceA.size;

  std::rotate(solution.path.begin(), solution.path.begin() + sliceB.index,
              solution.path.begin() + sliceB.index + sliceB.size);

  std::rotate(solution.path.begin() + sliceB.size,
              solution.path.begin() + sliceB.size + sliceA.size,
              solution.path.begin() + sliceB.index + sliceB.size);

  return solution;
}