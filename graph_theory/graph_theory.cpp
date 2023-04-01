#include <iostream>
#include "src/CommandManager.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	CommandManager cm(argc, argv);

	// вызов главной функции 
	cm.Run();

	return 0;
}
