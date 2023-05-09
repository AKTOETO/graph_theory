#include <iostream>
#include "src/CommandManager.h"


int main(int argc, char* argv[])
{
	std::locale::global(std::locale("ru"));
	CommandManager cm(argc, argv);
	
	// вызов главной функции 
	cm.Run();
	/*EdgeList ed =
	{
		{1,1,1},
		{2,3,5},
		{3,1,8},
		{1,6,10},
	};

	Graph gr(ed);
	gr.PrintAdjacencyMatrix();*/

	return 0;
}
