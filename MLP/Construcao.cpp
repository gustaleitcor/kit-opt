
#include "./MLP.h"
#include <algorithm>

void MLP::Construcao(Solution &solution, Data *data) {
  Solution s;
  size_t selection;
  double alpha;

  s.sequence.push_back(solution.sequence[0]);

  size_t node = solution.sequence[0];

  solution.sequence.erase(solution.sequence.begin());
  solution.sequence.pop_back();

  while (!solution.sequence.empty()) {
    std::sort(solution.sequence.begin(), solution.sequence.end(),
              [node, data](const int &a, const int &b) {
                return data->getDistance(a, node) < data->getDistance(b, node);
              });

    alpha = (double)rand() / RAND_MAX;
    selection = rand() % ((size_t)ceil(alpha * solution.sequence.size()));

    node = solution.sequence[selection];
    s.sequence.push_back(node);

    solution.sequence.erase(solution.sequence.begin() + selection);
  }

  s.sequence.push_back(s.sequence[0]);

  solution = s;
}