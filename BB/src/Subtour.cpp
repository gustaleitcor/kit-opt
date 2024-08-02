#include "Subtour.h"
#include "hungarian.h"
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

std::vector<Subtour::Subtour_t>
Subtour::findAllSubtours(hungarian_problem_t &hp) {

  int initial_node = 0, node = 0, length = 1;
  std::vector<int> not_visited_nodes(hp.num_cols);
  std::iota(not_visited_nodes.begin(), not_visited_nodes.end(), 0);

  std::vector<Subtour_t> subtours;

  for (int i = 0; i < hp.num_rows; i++) {
    if (hp.assignment[0][i] == 1) {
      initial_node = i;
      break;
    }
  }

  not_visited_nodes[0] = -1;
  not_visited_nodes[initial_node] = -1;

  for (int i = 1; i < hp.num_cols; i++) {
    for (int j = 0; j < hp.num_rows; j++) {
      if (hp.assignment[node][j] == 1) {
        length++;
        if (not_visited_nodes[j] == -1) {
          subtours.push_back(Subtour_t{std::pair(initial_node, node), length});
          for (auto n : not_visited_nodes) {
            if (n != -1) {
              initial_node = n;
              node = n;
              not_visited_nodes[n] = -1;
              i++;
              length = 0;
              break;
            }
          }
        } else {
          not_visited_nodes[j] = -1;
          node = j;
        }
      }
    }
  }

  return subtours;
}