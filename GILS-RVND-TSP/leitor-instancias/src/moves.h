#pragma once
#include "utils.h"
#include <cstddef>
#include <vector>

typedef struct SwapInfo_t {
  size_t i, j;
  double delta;
} SwapInfo;

inline bool bestImprovementSwap(Solution &solution, Data *data) {

  double delta;
  double xy, yz;
  double ab, bc;

  double xb, bz;
  double ay, yc;

  double cd;
  double ac, cb, bd;

  size_t x, y, z, a, b, c, d;
  SwapInfo bestSwap = (SwapInfo){.i = 0, .j = 0, .delta = 0};

  // SWAP do primeiro elemento

  // a -> b -> c => a -> y -> c
  // x -> y -> z => x -> b -> z

  a = solution.path[solution.path.size() - 1];
  b = solution.path[0];
  c = solution.path[1];

  for (size_t i = 2; i < solution.path.size() - 1; i++) {
    x = solution.path[i - 1];
    y = solution.path[i];
    z = solution.path[i + 1];

    ab = data->getDistance(a, b);
    bc = data->getDistance(b, c);
    yc = data->getDistance(y, c);
    ay = data->getDistance(a, y);

    xy = data->getDistance(x, y);
    yz = data->getDistance(y, z);
    xb = data->getDistance(x, b);
    bz = data->getDistance(b, z);

    delta = ay + yc + xb + bz - (ab + bc + xy + yz);

    if (delta < bestSwap.delta) {
      bestSwap.delta = delta;
      bestSwap.i = 0;
      bestSwap.j = i;
    };
  }

  // SWAP de não vizinhos

  // x -> y -> z => x -> b -> z
  // a -> b -> c => a -> y -> c

  for (size_t i = 1; i < solution.path.size() - 1; i++) {

    x = solution.path[i - 1];
    y = solution.path[i];
    z = solution.path[i + 1];

    xy = data->getDistance(x, y);
    yz = data->getDistance(y, z);

    for (size_t j = i + 2; j < solution.path.size() - 1; j++) {
      a = solution.path[j - 1];
      b = solution.path[j];
      c = solution.path[j + 1];

      ab = data->getDistance(a, b);
      bc = data->getDistance(b, c);

      xb = data->getDistance(x, b);
      bz = data->getDistance(b, z);

      ay = data->getDistance(a, y);
      yc = data->getDistance(y, c);

      delta = xb + bz + ay + yc - (xy + yz + ab + bc);

      if (delta < bestSwap.delta) {
        bestSwap.delta = delta;
        bestSwap.i = i;
        bestSwap.j = j;
      };
    }
  }

  // SWAP de vizinhos

  // a -> b -> c -> d => a -> c -> b -> d

  for (size_t i = 1; i < solution.path.size() - 2; i++) {

    a = solution.path[i - 1];
    b = solution.path[i];
    c = solution.path[i + 1];
    d = solution.path[i + 2];

    ab = data->getDistance(a, b);
    bc = data->getDistance(b, c);
    cd = data->getDistance(c, d);

    ac = data->getDistance(a, c);
    cb = data->getDistance(c, b);
    bd = data->getDistance(b, d);

    delta = ac + cb + bd - (ab + bc + cd);

    if (delta < bestSwap.delta) {
      bestSwap.delta = delta;
      bestSwap.i = i;
      bestSwap.j = i + 1;
    };
  }

  // SWAP do ultimo elemento

  // a -> b -> c => a -> y -> c
  // x -> y -> z => x -> b -> z

  a = solution.path[solution.path.size() - 2];
  b = solution.path[solution.path.size() - 1];
  c = solution.path[0];

  for (size_t i = 1; i < solution.path.size() - 2; i++) {
    x = solution.path[i - 1];
    y = solution.path[i];
    z = solution.path[i + 1];

    ab = data->getDistance(a, b);
    bc = data->getDistance(b, c);
    ay = data->getDistance(a, y);
    yc = data->getDistance(y, c);

    xy = data->getDistance(x, y);
    yz = data->getDistance(y, z);
    xb = data->getDistance(x, b);
    bz = data->getDistance(b, z);

    delta = ay + xb + bz + yc - (ab + bc + xy + yz);

    if (delta < bestSwap.delta) {
      bestSwap.delta = delta;
      bestSwap.i = i;
      bestSwap.j = solution.path.size() - 1;
    };
  }

  // SWAP do primeiro com o ultimo

  // a -> b -> c -> d => a -> c -> b -> d

  a = solution.path[solution.path.size() - 2];
  b = solution.path[solution.path.size() - 1];
  c = solution.path[0];
  d = solution.path[1];

  ab = data->getDistance(a, b);
  bc = data->getDistance(b, c);
  cd = data->getDistance(c, d);

  ac = data->getDistance(a, c);
  cb = data->getDistance(c, b);
  bd = data->getDistance(b, d);

  delta = ac + cb + bd - (ab + bc + cd);

  if (delta < bestSwap.delta) {
    bestSwap.delta = delta;
    bestSwap.i = 0;
    bestSwap.j = solution.path.size() - 1;
  };

  if (bestSwap.delta < 0) {
    swap(solution.path, bestSwap.i, bestSwap.j);
    solution.cost += bestSwap.delta;
    return true;
  }

  return false;
}

inline bool bestImprovement2Opt(std::vector<int> &solution, Data *data) {
  std::vector<int> solutionCpy(solution);

  int index = randInt(0, solutionCpy.size());
  int sliceSize = solutionCpy.size() - randInt(index, solutionCpy.size() + 1);

  for (int i = 0; i < sliceSize / 2; i++) {
    swap(solutionCpy, index + i, index + sliceSize - 1 - i);
  }

  int originalCost = calcCost(solution, data);
  int newCost = calcCost(solutionCpy, data);

  if (newCost < originalCost) {
    solution = solutionCpy;
    return true;
  }

  return false;
}

inline bool bestImprovementOrOpt(std::vector<int> &solution, Data *data,
                                 int n) {

  std::vector<int> solutionCpy(solution);
  int reinsertionNumbers[n];
  int randomIndex;

  randomIndex = rand() % (solutionCpy.size() - n);

  for (int i = 0; i < n; i++) {
    reinsertionNumbers[i] = solutionCpy[randomIndex];
    solutionCpy.erase(solutionCpy.begin() + randomIndex);
  }

  randomIndex = rand() % (solutionCpy.size() - n);

  for (int i = n - 1; i > -1; i--) {
    solutionCpy.insert(solutionCpy.begin() + randomIndex,
                       reinsertionNumbers[i]);
  }

  int newCost = calcCost(solutionCpy, data);
  int originalCost = calcCost(solution, data);

  if (newCost < originalCost) {
    solution = solutionCpy;
    return true;
  } else {
    return false;
  }
}