#include "../pch.h"
#include "GraphManagerT2.h"

GraphManagerT2::GraphManagerT2(std::string _filepath, INPUT_FILE_TYPE _in_f_type)
// инициализация всех полей
	:BaseGraphManager(_filepath, _in_f_type)
{
	// характеристика - функция обработки
	m_specs =
	{

	};
};
GraphManagerT2::~GraphManagerT2()
{
	// очистка памяти

};

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

#define IF_CALC(_spec) if((*m_state_of_spec)[int(_spec)])
#define IF_NOT_CALC(_spec) if(!(*m_state_of_spec)[int(_spec)])

bool GraphManagerT2::CalculateIsConnected()
{

	return false;
}

bool GraphManagerT2::CalculateIsNotConnected()
{
	return false;
}

bool GraphManagerT2::CalculateConnectedComponents()
{
	return false;
}

bool GraphManagerT2::CalculateIsDigraphConnected()
{
	return false;
}

bool GraphManagerT2::CalculateIsDigraphNotConnected()
{
	return false;
}

bool GraphManagerT2::CalculateIsDigraphWeaklyConnected()
{
	return false;
}

bool GraphManagerT2::CalculateIsDigraphStronglyConnected()
{
	return false;
}

bool GraphManagerT2::CalculateStronglyConnectedComponents()
{
	return false;
}

//==================================//
//            GET МЕТОДЫ            //
//==================================//


 

#undef IF_CALC
#undef IF_NOT_CALC
