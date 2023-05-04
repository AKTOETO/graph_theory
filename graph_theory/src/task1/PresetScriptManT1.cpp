#include "../pch.h"
#include "PresetScriptManT1.h"

PresetScriptManrT1::PresetScriptManrT1(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPreset(_graph_man)
{
	/*m_specs =
	{
		{SPEC::SHORTEST_DIST_MATR,	&PresetScriptManrT1::PrintShortestDistMatrix},
		{SPEC::ECCENTR,				&PresetScriptManrT1::PrintEccentricity},
		{SPEC::CENTRAL_VERT,		&PresetScriptManrT1::PrintCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&PresetScriptManrT1::PrintPeripheralVertices},
		{SPEC::RADIUS,				&PresetScriptManrT1::PrintRadius},
		{SPEC::DIAMETER,			&PresetScriptManrT1::PrintDiameter},
		{SPEC::DEGREES_IN,			&PresetScriptManrT1::PrintVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&PresetScriptManrT1::PrintVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&PresetScriptManrT1::PrintVertexDegreesInOut},
	};*/
}

PresetScriptManrT1::~PresetScriptManrT1()
{
	m_graph_manager.reset();
}

//#define G_MAN_PRES m_graph_manager->GetMajorPreset()
//#define IF_CALC(_spec) if((*G_MAN_PRES->GetStatesOfSpecs())[int(_spec)])

void PresetScriptManrT1::PrintShortestDistMatrix() const
{
	// если была расчитана матрица кратчайших расстояний
	IF_CALC(SPEC::SHORTEST_DIST_MATR)
	{
		INFO("печать матрицы кратчайших расстояний");

		std::cout << "Distancies:\n";
		auto mat = *G_MAN_PRES->GetShortestDistMatr();
		int print_width = CountDigitInMatrix(mat);
		for (auto& el : mat)
		{
			std::cout << "[";
			PrintVector(el, " ", print_width);
			std::cout << "]\n";
		}
	}
}

void PresetScriptManrT1::PrintEccentricity() const
{
	// если были расчитаны эксцентриситеты
	IF_CALC(SPEC::ECCENTR)
	{
		INFO("Печать массива эксцентриситетов");
		std::cout << "Eccentricity: [";
		PrintVector(*G_MAN_PRES->GetEccentricity(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManrT1::PrintCentralVertices() const
{
	IF_CALC(SPEC::CENTRAL_VERT)
	{
		INFO("печать центральных вершин");
		std::cout << "Z = [";
		PrintVector(*G_MAN_PRES->GetCentralVertices(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManrT1::PrintPeripheralVertices() const
{
	IF_CALC(SPEC::PERIPHERAL_VERT)
	{
		INFO("печать периферийных вершин");
		std::cout << "P = [";
		PrintVector(*G_MAN_PRES->GetPeripheralVertices(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManrT1::PrintRadius() const
{
	IF_CALC(SPEC::RADIUS)
	{
		INFO("печать радиуса");
		std::cout << "R = " << *G_MAN_PRES->GetRadius() << std::endl;
	}
}

void PresetScriptManrT1::PrintDiameter() const
{
	IF_CALC(SPEC::DIAMETER)
	{
		INFO("печать диаметра");
		std::cout << "D = " << *G_MAN_PRES->GetDiameter() << std::endl;
	}
}

void PresetScriptManrT1::PrintVertexDegreesIn() const
{
	// если были расчитаны степени входа
	IF_CALC(SPEC::DEGREES_IN)
	{
		INFO("печать степени входа");
		std::cout << "deg+ = [";
		PrintVector(*G_MAN_PRES->GetVertexDegreesIn(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManrT1::PrintVertexDegreesOut() const
{
	// если были расчитаны степени выхода
	IF_CALC(SPEC::DEGREES_OUT)
	{
		INFO("печать степени выхода");
		std::cout << "deg- = [";
		PrintVector(*G_MAN_PRES->GetVertexDegreesOut(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManrT1::PrintVertexDegreesInOut() const
{
	// если были расчитаны степени входа и выхода
	IF_CALC(SPEC::DEGREES_IN_OUT)
	{
		INFO("печать степени входа и выхода");
		std::cout << "deg = [";
		PrintVector(*G_MAN_PRES->GetVertexDegreesInOut(), ", ");
		std::cout << "]\n";
	}
}
