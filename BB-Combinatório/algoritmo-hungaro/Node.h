#pragma once
#include <string>
#include <vector>

using namespace std;

bool isSame(vector<vector<int>> v1, vector<vector<int>> v2) {
  if (v1.size() != v2.size()) {
    return false;
  }

  for (int i = 0; i < v1.size(); i++) {
    if (v1[i].size() != v2[i].size()) {
      return false;
    }

    for (int j = 0; j < v1[i].size(); j++) {
      if (v1[i][j] != v2[i][j]) {
        return false;
      }
    }
  }

  return true;
}

class Node {
public:
  Node(){};
  virtual ~Node(){};

  std::vector<vector<int>> forbidden_arcs;
  std::vector<std::vector<int>> subTour;
  double lower_bound;
  int chosen;
  bool feasible;

  bool operator==(const Node s) const {
    return (isSame(subTour, s.subTour) &&
            isSame(forbidden_arcs, s.forbidden_arcs));
  }
  bool operator!=(const Node s) const { return !operator==(s); }
};
