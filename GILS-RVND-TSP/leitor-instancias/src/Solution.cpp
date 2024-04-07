#include "Solution.h"
#include "Data.h"
#include <cstddef>
#include <numeric>
#include <vector>

Solution::Solution() { // Initializes empty
  this->cost = 0;
  this->path = std::vector<int>();
}

Solution::Solution(size_t n) { // Initializes with nodes, but cost set to zero
  this->path = std::vector<int>(n);
  std::iota(this->path.begin(), this->path.end(), 1); // @PG
  this->cost = 0;
}

Solution::Solution(size_t n,
                   Data *data) { // Initializes with nodes and sets initial cost
  this->path = std::vector<int>(n);
  std::iota(this->path.begin(), this->path.end(), 1); // @PG
  updateCost(data);
}

void Solution::updateCost(Data *data) {

  if (path.size() < 2) {
    return;
  }

  for (int i = 0; i < this->path.size() - 1; i++) {
    this->cost += data->getDistance(this->path[i], this->path[i + 1]);
  }
  this->cost += data->getDistance(this->path[path.size() - 1], this->path[0]);
}

double Solution::calcCost(const std::vector<int> &path, Data *data) {

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

void Solution::printPath(bool hamilton) {
  for (int i = 0; i < this->path.size(); i++) {
    std::cout << this->path[i] << (i != this->path.size() - 1 ? " -> " : "");
  }

  if (hamilton)
    std::cout << "->" << this->path[0] << std::endl;
  else
    std::cout << std::endl;
}

void Solution::printPath(std::vector<int> v, bool hamilton) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << (i != v.size() - 1 ? " -> " : "");
  }

  if (hamilton)
    std::cout << "->" << v[0] << std::endl;
  else
    std::cout << std::endl;
}

void Solution::swap(std::vector<int> &v, int i, int j) {
  int aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}
