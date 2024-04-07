#include "Subsequence.h"

Subsequence Subsequence::concatenate(Subsequence &sigma_1, Subsequence &sigma_2,
                                     Data *data) {

  Subsequence sigma;
  double temp = data->getDistance(sigma_1.last, sigma_2.first);
  sigma.W = sigma_1.W + sigma_2.W;
  sigma.T = sigma_1.T + temp + sigma_2.T;
  sigma.C = sigma_1.C + sigma_2.W * (sigma_1.T + temp) + sigma_2.C;
  sigma.first = sigma_1.first;
  sigma.last = sigma_2.last;

  return sigma;
}

Subsequence Subsequence::concatenate(Subsequence &s, Data *data) {

  Subsequence sigma;
  double temp = data->getDistance(this->last, s.first);
  sigma.W = this->W + s.W;
  sigma.T = this->T + temp + s.T;
  sigma.C = this->C + s.W * (this->T + temp) + s.C;
  sigma.first = this->first;
  sigma.last = s.last;

  return sigma;
}

void Subsequence::updateAllSubseq(
    Solution &s, std::vector<std::vector<Subsequence>> &subseq_matrix,
    Data *data) {
  size_t n = subseq_matrix.size();

  for (int i = 0; i < n; i++) {
    int v = s.path[i];
    subseq_matrix[i][i].W = (i > 0);
    subseq_matrix[i][i].C = 0;
    subseq_matrix[i][i].T = 0;
    subseq_matrix[i][i].first = s.path[i];
    subseq_matrix[i][i].last = s.path[i];
  }

  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      subseq_matrix[i][j] = Subsequence::concatenate(subseq_matrix[i][j - 1],
                                                     subseq_matrix[j][j], data);

  for (int i = n - 1; i >= 0; i--)
    for (int j = i - 1; j >= 0; j--)
      subseq_matrix[i][j] = Subsequence::concatenate(subseq_matrix[i][j + 1],
                                                     subseq_matrix[j][j], data);

  s.cost = subseq_matrix[0][n - 1].C;
}