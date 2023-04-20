#include <iostream>
#include "src/CommandManager.h"


int main(int argc, char* argv[])
{
	std::locale::global(std::locale("ru"));
	CommandManager cm(argc, argv);

	// вызов главной функции 
	cm.Run();

	return 0;
}
