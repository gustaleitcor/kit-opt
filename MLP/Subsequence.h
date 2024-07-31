#pragma once
#include "./Solution.h"
#include <vector>

class Subsequence {
public:
  double T, C;
  int W;
  int first, last;

  static void
  updateAllSubseq(Solution &s,
                  std::vector<std::vector<Subsequence>> &subseq_matrix,
                  Data *data);

  static Subsequence concatenate(Subsequence &s_1, Subsequence &s_2,
                                 Data *data);
  Subsequence concatenate(Subsequence &s, Data *data);
};
