#pragma once
#include "../parser/Data.h"
#include "./Solution.h"
#include "./Subsequence.h"

namespace MLP {
Solution MLP(Data *data);

void Construcao(Solution &solution, Data *data);

void BuscaLocal(Solution &solution, Data *data,
                std::vector<std::vector<Subsequence>> &subseq_matrix);

bool bestImprovementSwap(Solution &solution, Data *data,
                         std::vector<std::vector<Subsequence>> &subseq_matrix);

bool bestImprovement2Opt(Solution &solution, Data *data,
                         std::vector<std::vector<Subsequence>> &subseq_matrix);

bool bestImprovementOrOpt(Solution &solution, Data *data,
                          std::vector<std::vector<Subsequence>> &subseq_matrix,
                          int n);

Solution Pertubacao(Solution solution, Data *data);
} // namespace MLP
