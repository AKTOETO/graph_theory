#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <codecvt>

//
//#define TASK_FILES 15
//
//std::wstring readFile(const char* filename)
//{
//	std::wifstream wif(filename);
//	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
//	std::wstringstream wss;
//	wss << wif.rdbuf();
//	return wss.str();
//}
//
//int main()
//{
//	std::locale::global(std::locale::classic());
//	system("chcp 65001 > nul");
//
//	std::stringstream ss;
//	std::string numb;
//	std::string cmnd;
//	// цикл по всем файлам
//	for (int i = 1; i < TASK_FILES; i++)
//	{
//		ss << std::fixed << std::setw(3) << std::setfill('0') << i;
//		numb = ss.str();
//
//		cmnd = "graph_theory.exe -m \"matrix_t1_" + numb + ".txt\" -o \"out.txt\"";
//		system(cmnd.c_str());
//
//		// открытие файла с результатом и печать его в консоль
//		std::wstring str = readFile("assets/results/out.txt");
//
//		str = readFile("assets/results/out.txt");
//		std::wcout << str << std::endl;
//
//		std::wcout << "===================================\n\n";
//		ss.str("");
//	}
//	return 0;
//}
