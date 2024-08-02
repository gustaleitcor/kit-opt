#ifndef SUBTOUR_H
#define SUBTOUR_H

#include "hungarian.h"
#include <utility>
#include <vector>

namespace Subtour {

typedef struct {
  std::pair<int, int> bound;
  int length;
} Subtour_t;

std::vector<Subtour_t> findAllSubtours(hungarian_problem_t &hp);
} // namespace Subtour

#endif