#include <iostream>
#include "data.cpp"
#include "hungarian.cpp"
#include "./auxFunctions/subTourFinder.h"
#include "./auxFunctions/printVector.h"
#include "./auxFunctions/calcCost.h"
#include "Node.h"
#include <list>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

	Data *data = new Data(argc, argv[1]);
	data->readData();

	double **cost = new double *[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++)
	{
		cost[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++)
		{
			cost[i][j] = data->getDistance(i, j);
		}
	}

	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	double obj_value = hungarian_solve(&p);
	cout << "Obj. value: " << obj_value << endl;

	// cout << "Assignment" << endl;
	// hungarian_print_assignment(&p);

	vector<vector<int>> subTours;

	subTours = subTourFinder(&p);

	for (vector<int> i : subTours)
	{
		std::cout << "{ ";
		printVector(i, false);
		std::cout << " } ";
	}
	std::cout << std::endl;

	double **costCpy = new double *[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++)
	{
		costCpy[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++)
		{
			costCpy[i][j] = data->getDistance(i, j);
		}
	}

	list<Node> tree;

	Node currentNode;
	Node auxNode;
	vector<int> auxForbidden_arcs;

	vector<vector<int>> previousSubTour;

	vector<int> minSubTour;
	unsigned int minSubTour_length = 999999;

	tree.push_back(currentNode);

	int loop = 100;

	//----------------------------------------------------------//

	while (currentNode.subTour.size() != 1)
	{
		currentNode = get(tree, 0);

		for (int j = 0; j < data->getDimension(); j++)
		{
			for (int i = 0; i < data->getDimension(); i++)
			{
				costCpy[i][j] = cost[i][j];
			}
		}

		if (currentNode.forbidden_arcs.size() > 0)
		{
			for (vector<int> i : currentNode.forbidden_arcs)
			{
				costCpy[i[0]][i[1]] = 999999999;
			}
		}

		hungarian_init(&p, costCpy, data->getDimension(), data->getDimension(), mode); // Carregando o problema
		hungarian_solve(&p);
		currentNode.subTour = subTourFinder(&p);

		for (vector<int> i : currentNode.subTour)
		{
			if (i.size() < minSubTour_length)
			{
				minSubTour = i;
				minSubTour_length = i.size();
			}
		}

		minSubTour_length = 999999;
		auxNode.subTour = currentNode.subTour;
		auxNode.forbidden_arcs = currentNode.forbidden_arcs;

		for (int i = 0; i < minSubTour.size() - 1; i++)
		{
			auxForbidden_arcs.push_back(minSubTour[i]);
			auxForbidden_arcs.push_back(minSubTour[i + 1]);

			auxNode.forbidden_arcs.push_back(auxForbidden_arcs);

			auxForbidden_arcs.clear();

			tree.push_back(auxNode);
		}

		auxForbidden_arcs = {minSubTour[minSubTour.size() - 1], minSubTour[0]};
		auxNode.forbidden_arcs.push_back(auxForbidden_arcs);

		auxForbidden_arcs.clear();

		tree.push_back(auxNode);

		tree.pop_front();

		if (false)
		{
			break;
		}
	}

	//----------------------------------------------------------//

	for (vector<int> i : currentNode.subTour)
	{
		std::cout << "{ ";
		printVector(i, false);
		std::cout << " } ";
	}
	std::cout << std::endl;

	std::cout << "Custo = " << calcCost(currentNode.subTour[0], data) << std::endl;

	// hungarian_print_costmatrix(&p);

	hungarian_free(&p);
	for (int i = 0; i < data->getDimension(); i++)
		delete[] cost[i];
	delete[] cost;
	delete data;

	return 0;
}
