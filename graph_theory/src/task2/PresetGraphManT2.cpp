#include "../pch.h"
#include "PresetGraphManT2.h"

PresetGraphManT2::PresetGraphManT2(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states)
// инициализация всех полей
	:BaseGraphManager(_graph, _states)
{};
PresetGraphManT2::~PresetGraphManT2()
{
	// очистка памяти

};

//==================================//
//         CALCULATE МЕТОДЫ         //
//==================================//

//#define IF_ST_CALC(_spec) if((*m_state_of_spec)[int(_spec)])
//#define IF_ST_NOT_CALC(_spec) if(!(*m_state_of_spec)[int(_spec)])

bool PresetGraphManT2::CalculateIsConnected()
{
	
	return false;
}

bool PresetGraphManT2::CalculateIsNotConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateConnectedComponents()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphNotConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphWeaklyConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateIsDigraphStronglyConnected()
{
	return false;
}

bool PresetGraphManT2::CalculateStronglyConnectedComponents()
{
	return false;
}

//==================================//
//            GET МЕТОДЫ            //
//==================================//


 

#undef IF_CALC
#undef IF_NOT_CALC
