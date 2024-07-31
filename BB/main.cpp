#include <iostream>
using namespace std;

#include "../parser/data.h"
#include "hungarian.h"

int main(int argc, char** argv) {

	Data * data = new Data(argc, argv[1]);
	data->readData();

	double **matrix_cost = new double*[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++){
		matrix_cost[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++){
			matrix_cost[i][j] = data->getDistance(i,j);
		}
	}

	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, matrix_cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	double obj_value = hungarian_solve(&p);
	cout << "Obj. value: " << obj_value << endl;

	cout << "Assignment" << endl;
	hungarian_print_assignment(&p);

	hungarian_free(&p);
	for (int i = 0; i < data->getDimension(); i++) delete [] matrix_cost[i];
	delete [] matrix_cost;
	delete data;

	return 0;
}