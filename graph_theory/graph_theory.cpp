#include <iostream>
#include "src/Graph.h"


int main()
{
	setlocale(LC_ALL, "ru");

	Graph gr("adjacency_matrix.txt",INPUT_FILE_TYPE::ADJACENCY_MATRIX);

	gr.PrintAdjacencyMatrix();

	return 0;
}
