#pragma once
#include "./utils.h"
#include "Data.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

#include <iostream>
using namespace std;

typedef struct InsertionInfo_t {
  size_t i, j, k;
  double cost;
} InsertionInfo;

inline void Construcao(Solution &solution, Data *data) {
  vector<int> path;

  path.push_back(solution.path[0]);
  path.push_back(solution.path[0]);

  solution.path.erase(solution.path.begin());

  double total_dist = calcCost(path, data);

  double cost;
  size_t ik;
  size_t kj;
  size_t ij;

  std::vector<InsertionInfo> vcost;

  while (!solution.path.empty()) {
    for (size_t i = 0; i < path.size() - 1; i++) {
      // i = i
      // j = i + 1
      // k = k
      for (size_t k = 0; k < solution.path.size(); k++) {
        ik = data->getDistance(path[i], solution.path[k]);
        kj = data->getDistance(solution.path[k], path[i + 1]);
        ij = data->getDistance(path[i], path[i + 1]);
        cost = ik + kj - ij;

        vcost.push_back(
            (InsertionInfo){.i = i, .j = i + 1, .k = k, .cost = cost});
      }
    }

    std::sort(vcost.begin(), vcost.end(),
              [](const InsertionInfo &a, const InsertionInfo &b) {
                return a.cost < b.cost;
              });

    // bias towards begin
    double alpha = (double)rand() / RAND_MAX;
    size_t selection = rand() % ((size_t)ceil(alpha * vcost.size()));

    total_dist += vcost[selection].cost;
    path.insert(path.begin() + vcost[selection].j,
                solution.path[vcost[selection].k]);
    solution.path.erase(solution.path.begin() + vcost[selection].k);

    vcost.clear();
  }

  path.pop_back();

  if (total_dist < solution.cost) {
    solution.path = path;
    solution.cost = total_dist;
  } else {
    solution.path.resize(data->getDimension());
    std::iota(solution.path.begin(), solution.path.end(), 1);
  }
}

// LEGACY

// typedef struct MinorCost_t {
//   double cost;
//   int j;
//   int k;
//   bool isUpdated = false;
// } MinorCost;

// std::cout << path.size() << std::endl;
// printPath(path);

// return;

// MinorCost minorCost;
// while (!solution.path.empty()) {
//   for (int i = 0; i < path.size() - 1; i++) {
//     for (int j = 0; j < solution.path.size(); j++) {
//       ik = data->getDistance(path[i], solution.path[j]);
//       kj = data->getDistance(solution.path[j], path[i + 1]);
//       ij = data->getDistance(path[i], path[i + 1]);
//       cost = ik + kj - ij;

//       if (!minorCost.isUpdated) {
//         minorCost.isUpdated = true;
//         minorCost.cost = cost;
//         minorCost.j = i + 1;
//         minorCost.k = j;
//       } else if (minorCost.cost > cost) {
//         minorCost.cost = cost;
//         minorCost.j = i + 1;
//         minorCost.k = j;
//       }
//     }
//   }

//   minorCost.isUpdated = false;

//   tDist += minorCost.cost;
//   path.insert(path.begin() + minorCost.j, solution.path[minorCost.k]);
//   solution.path.erase(solution.path.begin() + minorCost.k);
// }

// path.pop_back();

// solution.path = path;