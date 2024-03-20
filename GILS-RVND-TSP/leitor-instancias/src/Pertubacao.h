#pragma once
#include "./BuscaLocal.h"
#include "./utils.h"
#include "Data.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <vector>

const double magnitude = 1;

struct slice {
  size_t index;
  size_t size;
};

inline bool Pertubacao(Solution &solution, Data *data) {
  struct slice sliceA;
  struct slice sliceB;

  sliceA.index = rand() % solution.path.size();

  if (solution.path.size() < 30)
    sliceA.size = 2;
  else
    sliceA.size = ceil(rand() % (solution.path.size() / 10 - 2)) + 2;

  std::rotate(solution.path.begin(), solution.path.begin() + sliceA.index,
              solution.path.end());

  sliceB.index = rand() % (solution.path.size() - sliceA.size) + sliceA.size;

  if (solution.path.size() < 30)
    sliceB.size = 2;
  else
    sliceB.size =
        ceil(rand() % ((solution.path.size() - sliceA.size) / 10 - 2)) + 2;

  std::cout << sliceA.index << ' ' << sliceA.size << std::endl;
  std::cout << sliceB.index << ' ' << sliceB.size << std::endl;
  printPath(solution.path);

  return true;
}

// LEGACY

// vector<int> solutionCpy(solution);

// int indexA = randInt(0, solutionCpy.size());
// int sliceSizeA =
//     magnitude * (solutionCpy.size() - randInt(indexA, solutionCpy.size())) /
//         10 +
//     1;

// int sliceA[sliceSizeA];

// for (int i = 0; i < sliceSizeA; i++) {
//   sliceA[i] = solutionCpy[indexA];
//   solutionCpy.erase(solutionCpy.begin() + indexA);
// }

// int indexB = randInt(0, solutionCpy.size());
// int sliceSizeB;

// if (indexB < indexA) {
//   sliceSizeB = magnitude * (indexA - randInt(indexB, indexA)) / 10 + 1;
// } else {
//   sliceSizeB =
//       magnitude * (solutionCpy.size() - randInt(indexB, solutionCpy.size()))
//       /
//           10 +
//       1;
// }

// int sliceB[sliceSizeB];

// for (int i = 0; i < sliceSizeB; i++) {
//   sliceB[i] = solutionCpy[indexB];
//   solutionCpy.erase(solutionCpy.begin() + indexB);
// }

// for (int i = 0; i < solution.size(); i++) {
//   solutionCpy.push_back(-1);
// }

// for (int i = 0; i < sliceSizeA; i++) {
//   solutionCpy.insert(solutionCpy.begin() + indexB, sliceA[i]);
// }

// for (int i = 0; i < sliceSizeB; i++) {
//   solutionCpy.insert(solutionCpy.begin() + indexA, sliceB[i]);
// }

// for (int i = solutionCpy.size(); i >= 0; i--) {
//   if (solutionCpy[i] == -1) {
//     solutionCpy.erase(solutionCpy.begin() + i);
//   }
// }

// BuscaLocal(solutionCpy, data);

// if (calcCost(solutionCpy, data) < calcCost(solution, data)) {
//   solution = solutionCpy;
//   return true;
// }

// return false;