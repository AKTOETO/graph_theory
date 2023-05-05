#include <iostream>
#include "src/CommandManager.h"


int main(int argc, char* argv[])
{
	std::locale::global(std::locale("ru"));
	CommandManager cm(argc, argv);
	
	// вызов главной функции 
	cm.Run();
	/*Graph gr("task2/matrix_t2_001.txt", INPUT_FILE_TYPE::ADJACENCY_MATRIX);
	for (auto& el : gr.adjacency_list(5))
	{
		std::cout << el << " ";
	}*/

	return 0;
}
