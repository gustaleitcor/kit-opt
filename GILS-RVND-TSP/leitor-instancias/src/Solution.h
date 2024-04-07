#pragma once
#include "./Data.h"
#include <cstddef>
#include <vector>

class Solution {
public:
  std::vector<int> path;
  double cost;

  Solution();
  Solution(size_t n);
  Solution(size_t n, Data *data);

  void updateCost(Data *data);
  static double calcCost(const std::vector<int> &v, Data *data);
  void printPath(bool hamilton = true);
  static void printPath(std::vector<int> v, bool hamilton = true);
  static void swap(std::vector<int> &v, int i, int j);
};