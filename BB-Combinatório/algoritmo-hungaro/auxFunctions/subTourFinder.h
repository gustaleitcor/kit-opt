#pragma once
#include "../Node.h"
#include "../hungarian.cpp"
#include <iostream>
#include <list>
#include <vector>


int get(list<int> _list, int _i) {
  list<int>::iterator it = _list.begin();
  for (int i = 0; i < _i; i++) {
    ++it;
  }
  return *it;
}

Node get(list<Node> _list, int _i) {
  list<Node>::iterator it = _list.begin();
  for (int i = 0; i < _i; i++) {
    ++it;
  }
  return *it;
}

vector<vector<int>> subTourEngine(int **C, int rows, int cols) {
  vector<int> path;

  for (int j = 0; j < rows; j++) {
    for (int i = 0; i < cols; i++) {
      if (C[i][j] == 1) {
        path.push_back(i);
        break;
      }
    }
  }

  int index = 0;
  int first = 0;
  vector<int> subTour;
  vector<vector<int>> subTours;
  list<int> avbNodes(path.begin(), path.end());

  for (int i = 0; i < path.size(); i++) {
    subTour.push_back(path[index]);
    if (path[index] == first) {
      avbNodes.remove(index);
      first = get(avbNodes, 0);
      index = first;
      subTours.push_back(subTour);
      subTour.clear();
    } else {
      avbNodes.remove(index);
      index = path[index];
    }
  }
  return subTours;
}

vector<vector<int>> subTourFinder(hungarian_problem_t *p) {
  return subTourEngine(p->assignment, p->num_rows, p->num_cols);
}
