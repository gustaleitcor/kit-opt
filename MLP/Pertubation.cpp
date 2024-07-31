#include "MLP.h"
#include <algorithm>

struct slice {
  size_t index;
  size_t size;
};

Solution MLP::Pertubacao(Solution solution, Data *data) {

  struct slice sliceA;
  struct slice sliceB;

  if ((solution.sequence.size() - 2) < 30)
    sliceA.size = 2;
  else
    sliceA.size = ceil(rand() % ((solution.sequence.size() - 2) / 10 - 2)) + 2;

  sliceA.index = rand() % ((solution.sequence.size() - 2) - sliceA.size + 1);

  std::rotate(solution.sequence.begin() + 1,
              solution.sequence.begin() + 1 + sliceA.index,
              solution.sequence.end() - 1);

  if ((solution.sequence.size() - 2) < 30)
    sliceB.size = 2;
  else
    sliceB.size =
        ceil(rand() %
             (((solution.sequence.size() - 2) - sliceA.size) / 10 - 2)) +
        2;

  sliceB.index = rand() % ((solution.sequence.size() - 2) - sliceA.size -
                           sliceB.size + 1) +
                 sliceA.size;

  std::rotate(solution.sequence.begin() + 1,
              solution.sequence.begin() + 1 + sliceB.index,
              solution.sequence.begin() + 1 + sliceB.index + sliceB.size);

  std::rotate(solution.sequence.begin() + 1 + sliceB.size,
              solution.sequence.begin() + 1 + sliceB.size + sliceA.size,
              solution.sequence.begin() + 1 + sliceB.index + sliceB.size);

  return solution;
}