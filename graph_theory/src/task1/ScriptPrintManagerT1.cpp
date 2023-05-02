#include "../pch.h"
#include "ScriptPrintManagerT1.h"

ScriptPrintManagerT1::ScriptPrintManagerT1(
	std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script
)
	: BaseScriptPrintManager(_filepath, _in_f_type, _script)
{
	m_specs =
	{
		{SPEC::SHORTEST_DIST_MATR,	&ScriptPrintManagerT1::PrintShortestDistMatrix},
		{SPEC::ECCENTR,				&ScriptPrintManagerT1::PrintEccentricity},
		{SPEC::CENTRAL_VERT,		&ScriptPrintManagerT1::PrintCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&ScriptPrintManagerT1::PrintPeripheralVertices},
		{SPEC::RADIUS,				&ScriptPrintManagerT1::PrintRadius},
		{SPEC::DIAMETER,			&ScriptPrintManagerT1::PrintDiameter},
		{SPEC::DEGREES_IN,			&ScriptPrintManagerT1::PrintVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&ScriptPrintManagerT1::PrintVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&ScriptPrintManagerT1::PrintVertexDegreesInOut},
	};
}

ScriptPrintManagerT1::~ScriptPrintManagerT1()
{
	m_graph_manager.reset();
	m_script.reset();
}

#define IF_CALC(_spec) if((*m_graph_manager->GetStatesOfSpecs())[int(_spec)])

void ScriptPrintManagerT1::PrintShortestDistMatrix() const
{
	// если была расчитана матрица кратчайших расстояний
	IF_CALC(SPEC::SHORTEST_DIST_MATR)
	{
		INFO("печать матрицы кратчайших расстояний");

		std::cout << "Distancies:\n";
		auto mat = *m_graph_manager->GetShortestDistMatr();
		int print_width = CountDigitInMatrix(mat);
		for (auto& el : mat)
		{
			std::cout << "[";
			PrintVector(el, " ", print_width);
			std::cout << "]\n";
		}
	}
}

void ScriptPrintManagerT1::PrintEccentricity() const
{
	// если были расчитаны эксцентриситеты
	IF_CALC(SPEC::ECCENTR)
	{
		INFO("Печать массива эксцентриситетов");
		std::cout << "Eccentricity: [";
		PrintVector(*m_graph_manager->GetEccentricity(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManagerT1::PrintCentralVertices() const
{
	IF_CALC(SPEC::CENTRAL_VERT)
	{
		INFO("печать центральных вершин");
		std::cout << "Z = [";
		PrintVector(*m_graph_manager->GetCentralVertices(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManagerT1::PrintPeripheralVertices() const
{
	IF_CALC(SPEC::PERIPHERAL_VERT)
	{
		INFO("печать периферийных вершин");
		std::cout << "P = [";
		PrintVector(*m_graph_manager->GetPeripheralVertices(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManagerT1::PrintRadius() const
{
	IF_CALC(SPEC::RADIUS)
	{
		INFO("печать радиуса");
		std::cout << "R = " << *m_graph_manager->GetRadius() << std::endl;
	}
}

void ScriptPrintManagerT1::PrintDiameter() const
{
	IF_CALC(SPEC::DIAMETER)
	{
		INFO("печать диаметра");
		std::cout << "D = " << *m_graph_manager->GetDiameter() << std::endl;
	}
}

void ScriptPrintManagerT1::PrintVertexDegreesIn() const
{
	// если были расчитаны степени входа
	IF_CALC(SPEC::DEGREES_IN)
	{
		INFO("печать степени входа");
		std::cout << "deg+ = [";
		PrintVector(*m_graph_manager->GetVertexDegreesIn(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManagerT1::PrintVertexDegreesOut() const
{
	// если были расчитаны степени выхода
	IF_CALC(SPEC::DEGREES_OUT)
	{
		INFO("печать степени выхода");
		std::cout << "deg- = [";
		PrintVector(*m_graph_manager->GetVertexDegreesOut(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManagerT1::PrintVertexDegreesInOut() const
{
	// если были расчитаны степени входа и выхода
	IF_CALC(SPEC::DEGREES_IN_OUT)
	{
		INFO("печать степени входа и выхода");
		std::cout << "deg = [";
		PrintVector(*m_graph_manager->GetVertexDegreesInOut(), ", ");
		std::cout << "]\n";
	}
}
