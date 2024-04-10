#include "../Subsequence.h"
#include "MLP.h"
#include <algorithm>

struct slice {
  size_t index;
  size_t size;
};

Solution MLP::Pertubacao(Solution solution, Data *data) {

  solution.sequence.pop_back();
  solution.sequence.erase(solution.sequence.begin());

  struct slice sliceA;
  struct slice sliceB;

  if (solution.sequence.size() < 30)
    sliceA.size = 2;
  else
    sliceA.size = ceil(rand() % (solution.sequence.size() / 10 - 2)) + 2;

  sliceA.index = rand() % (solution.sequence.size() - sliceA.size + 1);

  std::rotate(solution.sequence.begin(),
              solution.sequence.begin() + sliceA.index,
              solution.sequence.end());

  if (solution.sequence.size() < 30)
    sliceB.size = 2;
  else
    sliceB.size =
        ceil(rand() % ((solution.sequence.size() - sliceA.size) / 10 - 2)) + 2;

  sliceB.index =
      rand() % (solution.sequence.size() - sliceA.size - sliceB.size + 1) +
      sliceA.size;

  std::rotate(solution.sequence.begin(),
              solution.sequence.begin() + sliceB.index,
              solution.sequence.begin() + sliceB.index + sliceB.size);

  std::rotate(solution.sequence.begin() + sliceB.size,
              solution.sequence.begin() + sliceB.size + sliceA.size,
              solution.sequence.begin() + sliceB.index + sliceB.size);

  solution.sequence.push_back(1);
  solution.sequence.insert(solution.sequence.begin(), 1);

  return solution;
}