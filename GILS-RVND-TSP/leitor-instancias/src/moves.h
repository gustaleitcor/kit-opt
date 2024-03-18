#pragma once
#include "utils.h"
#include <algorithm>
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

typedef struct Info2opt {
  size_t i, j;
  double delta;
} Info2opt_t;

inline bool bestImprovement2Opt(Solution &solution, Data *data) {

  size_t a, b, c, d;
  double ab, cd, ac, bd;

  double delta;
  Info2opt best2opt = (Info2opt){
      .i = 0,
      .j = 0,
      .delta = 0,
  };

  for (size_t i = 0; i < solution.path.size(); i++) {
    for (size_t j = i + 2; j < solution.path.size() - 1; j++) {
      a = solution.path[i];
      b = solution.path[i + 1];
      c = solution.path[j];
      d = solution.path[j + 1];

      ab = data->getDistance(a, b);
      cd = data->getDistance(c, d);

      ac = data->getDistance(a, c);
      bd = data->getDistance(b, d);

      delta = ac + bd - (ab + cd);

      if (delta < best2opt.delta) {
        best2opt.delta = delta;
        best2opt.i = i + 1;
        best2opt.j = j + 1;
      }
    }
  }

  if (best2opt.delta < 0) {
    solution.cost += best2opt.delta;
    reverse(solution.path.begin() + best2opt.i,
            solution.path.begin() + best2opt.j);
    return true;
  }

  return false;
}

typedef struct OrOptInfo {
  size_t i, j;
  double delta;
} OrOptInfo_t;

inline bool bestImprovementOrOpt(Solution &solution, Data *data, int n) {
  size_t a, b, c, d, e, f, aux;
  double ab, cd, ad, eb, cf, ef;
  double delta;
  OrOptInfo bestOrOp = (OrOptInfo){.i = 0, .j = 0, .delta = 0};

  for (size_t i = 1; i < solution.path.size() - n; i++) {
    for (size_t j = 1; j < solution.path.size() - 1; j++) {

      if (j >= i - 1 && j < i + n)
        continue;

      // std::cout << i << ' ' << j << std::endl;

      a = solution.path[i - 1];
      b = solution.path[i];
      c = solution.path[i + n - 1];
      d = solution.path[i + n];

      e = solution.path[j];
      f = solution.path[j + 1];

      ab = data->getDistance(a, b);
      cd = data->getDistance(c, d);
      ad = data->getDistance(a, d);

      eb = data->getDistance(e, b);
      cf = data->getDistance(c, f);
      ef = data->getDistance(e, f);

      delta = ad + eb + cf - (ab + cd + ef);

      if (delta < bestOrOp.delta) {
        bestOrOp.delta = delta;
        bestOrOp.i = i;
        bestOrOp.j = j;
      }
    }
  }

  if (bestOrOp.delta < 0) {
    // if (bestOrOp.i > bestOrOp.j) {
    //   bestOrOp.j++;
    // }

    std::cout << "Best switch " << bestOrOp.i << ' ' << bestOrOp.j << std::endl;

    for (int i = 0; i < n; i++) {
      aux = solution.path[bestOrOp.i + (bestOrOp.i > bestOrOp.j ? i : 0)];
      solution.path.erase(solution.path.begin() + bestOrOp.i +
                          (bestOrOp.i > bestOrOp.j ? i : 0));
      solution.path.insert(solution.path.begin() + bestOrOp.j +
                               (bestOrOp.i > bestOrOp.j ? i : n - 1),
                           aux);
    }

    solution.cost += bestOrOp.delta;

    return true;
  }

  return false;
}