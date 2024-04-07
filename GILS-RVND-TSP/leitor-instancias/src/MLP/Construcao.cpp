
#include "../Subsequence.h"
#include "MLP.h"
#include <algorithm>

void MLP::Construcao(Solution &solution, Data *data) {
  Solution s;
  size_t selection;
  double alpha;

  s.path.push_back(solution.path[0]);

  size_t node = solution.path[0];

  solution.path.erase(solution.path.begin());

  while (!solution.path.empty()) {
    std::sort(solution.path.begin(), solution.path.end(),
              [node, data](const int &a, const int &b) {
                return data->getDistance(a, node) < data->getDistance(b, node);
              });

    alpha = (double)rand() / RAND_MAX;
    selection = rand() % ((size_t)ceil(alpha * solution.path.size()));

    node = solution.path[selection];
    s.path.push_back(node);

    solution.path.erase(solution.path.begin() + selection);
  }

  solution = s;
}