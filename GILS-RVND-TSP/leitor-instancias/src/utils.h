#pragma once

#include "./Data.h"

#include <iostream>
#include <vector>

typedef struct Solution {
  std::vector<int> path;
  double cost;
} Solution_t;

inline double calcCost(const std::vector<int> &path, Data *data) {

  if (path.size() < 2) {
    return 0;
  }

  double cost = 0;
  for (int i = 0; i < path.size() - 1; i++) {
    cost += data->getDistance(path[i], path[i + 1]);
  }

  cost += data->getDistance(path[path.size() - 1], path[0]);

  return cost;
}

inline void printPath(const std::vector<int> &path, bool hamilton = true) {
  for (int i : path) {
    std::cout << i << " -> ";
  }

  if (hamilton)
    std::cout << path[0] << std::endl;
  else
    std::cout << std::endl;
}

inline int randInt(int start__, int end__) {
  return (rand() % (end__ - start__)) + start__;
}

inline void swap(vector<int> &v, int i, int j) {
  int aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}