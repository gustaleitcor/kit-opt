#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Pertubacao.h"
#include "./auxFunctions/calcCost.h"
#include "./auxFunctions/printPath.h"

using namespace std;

int main(int argc, char **argv)
{

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    cout << "Dimension: " << n << endl;
    // cout << "DistanceMatrix: " << endl;
    // data.printMatrixDist();

    vector<int> path;
    double cost = 0;

    for (int i = 0; i < data.getDimension(); i++)
    {
        path.push_back(i + 1);
    }

    cout << "Custo = " << calcCost(path, &data) << endl;

    Construcao(path, &data);

    printPath(path);

    cout << "Custo = " << calcCost(path, &data) << endl;

    for (int i = 0; i < 100; i++)
        BuscaLocal(path, &data);

    printPath(path);

    cout << "Custo = " << calcCost(path, &data) << endl;

    for (int i = 0; i < 1000; i++)
        Pertubacao(path, &data);

    printPath(path);

    cout << "Custo = " << calcCost(path, &data) << endl;

    return 0;
}
