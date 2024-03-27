#pragma once
#include "../Solution.h"
#include <vector>

class Subsequence {
public:
  double T, C;
  int W;
  int first, last;

  Subsequence concatenate(Subsequence &s);
  Subsequence concatenate(Subsequence &s_1, Subsequence &s_2);
};

inline void
updateAllSubseq(Solution &s,
                std::vector<std::vector<Subsequence>> &subseq_matrix) {
  for (int i = 0; i < subseq_matrix.size(); i++) {
    // int v = s->sequence[i];
    // subseq_matrix[i][i].W = (i > 0);
    // subseq_matrix[i][i].C = 0;
    // subseq_matrix[i][i].T = 0;
    // subseq_matrix[i][i].first = s->sequence[i];
    // subseq_matrix[i][i].last = s->sequence[i];
  }
}