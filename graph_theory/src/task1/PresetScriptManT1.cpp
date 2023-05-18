#include "../pch.h"
#include "PresetScriptManT1.h"

PresetScriptManT1::PresetScriptManT1(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{}

PresetScriptManT1::~PresetScriptManT1()
{
	m_graph_manager.reset();
}

void PresetScriptManT1::PrintShortestDistMatrix() const
{
	// если была расчитана матрица кратчайших расстояний
	IF_CALC(SPEC::T1_SHORTEST_DIST_MATR)
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

void PresetScriptManT1::PrintEccentricity() const
{
	// если были расчитаны эксцентриситеты
	IF_CALC(SPEC::T1_ECCENTR)
	{
		INFO("Печать массива эксцентриситетов");
		std::cout << "Eccentricity: [";
		PrintVector(*G_MAN_PRES->GetEccentricity(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManT1::PrintCentralVertices() const
{
	IF_CALC(SPEC::T1_CENTRAL_VERT)
	{
		INFO("печать центральных вершин");
		std::cout << "Z = [";
		PrintVector(*G_MAN_PRES->GetCentralVertices(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManT1::PrintPeripheralVertices() const
{
	IF_CALC(SPEC::T1_PERIPHERAL_VERT)
	{
		INFO("печать периферийных вершин");
		std::cout << "P = [";
		PrintVector(*G_MAN_PRES->GetPeripheralVertices(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManT1::PrintRadius() const
{
	IF_CALC(SPEC::T1_RADIUS)
	{
		INFO("печать радиуса");
		std::cout << "R = " << *G_MAN_PRES->GetRadius() << std::endl;
	}
}

void PresetScriptManT1::PrintDiameter() const
{
	IF_CALC(SPEC::T1_DIAMETER)
	{
		INFO("печать диаметра");
		std::cout << "D = " << *G_MAN_PRES->GetDiameter() << std::endl;
	}
}

void PresetScriptManT1::PrintVertexDegreesIn() const
{
	// если были расчитаны степени входа
	IF_CALC(SPEC::T1_DEGREES_IN)
	{
		INFO("печать степени входа");
		std::cout << "deg+ = [";
		PrintVector(*G_MAN_PRES->GetVertexDegreesIn(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManT1::PrintVertexDegreesOut() const
{
	// если были расчитаны степени выхода
	IF_CALC(SPEC::T1_DEGREES_OUT)
	{
		INFO("печать степени выхода");
		std::cout << "deg- = [";
		PrintVector(*G_MAN_PRES->GetVertexDegreesOut(), ", ");
		std::cout << "]\n";
	}
}

void PresetScriptManT1::PrintVertexDegreesInOut() const
{
	// если были расчитаны степени входа и выхода
	IF_CALC(SPEC::T1_DEGREES_IN_OUT)
	{
		INFO("печать степени входа и выхода");
		std::cout << "deg = [";
		PrintVector(*G_MAN_PRES->GetVertexDegreesInOut(), ", ");
		std::cout << "]\n";
	}
}
