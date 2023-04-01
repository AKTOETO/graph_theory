#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

// путь до папки с файлами для графа
const std::string FILE_PATH = "assets/";


//==================//
//	В Е Р Ш И Н А	//
//==================//

// тип данных вершины
using Vertex = int;

// список вершин
using VertexArr = std::vector<Vertex>;

// матрица
using VertexMatrix = std::vector<VertexArr>;

//==============//
//	Р Е Б Р О	//
//==============//

// вес ребра
using Weight = int;

// ребро
struct Edge
{
	Vertex m_from;	// вершина, откуда исходир ребро
	Vertex m_to;	// вершина, куда идет ребро
	Weight m_weight;// вес ребра
};

// список ребер
using EdgeArr = std::vector<Edge>;


//==============//
//	Д И А Л О Г	//
//==============//

// путь к описаниям команд
const std::string MSG_DECR_FOLDER = "assets/messages/";

// строка слева от введенной команды
const std::string DBMS_CONSOLE_REQUEST_COMMAND = "\n[СУБД v1.0]> ";

// сообщение о некорректных данных
const std::string NOT_CORRECT_DATA = "-";

// сообщение об ошибочном вводе команды
const std::string NOT_CORRECT_COMMAND = " такой команды не существует\n\
Если неизвестны команды, введите: помощь\n\
Если не знаете, как пользоваться командой, \
введите: помощь <неизвестная команда>\n";

// количество команд
const int NUMBER_OF_COMMANDS = 1;

// ПРИ ДОБАВЛЕНИИ КОМАНДЫ НАДО ЕЩЕ ДОБАВИТЬ 
// В COMMAND_CHECK_FUNCTIONS УКАЗАТЕЛИ НА СОТВЕТСТВУЮЩИЕ 
// ФУНКЦИИ В КОНСТРУКТОРЕ Menu()
// массив с файлами, в которых лежит описание команд
const std::string COMMAND_DESCRIPTION_FILES[NUMBER_OF_COMMANDS] =
{
	"help.txt",
};

#endif // CONSTANTS_H
