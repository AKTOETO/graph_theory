#include "../pch.h"
#include "PresetScriptManT3.h"

PresetScriptManT3::PresetScriptManT3(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPreset(_graph_man)
{}

PresetScriptManT3::~PresetScriptManT3()
{
	m_graph_manager.reset();
}

void PresetScriptManT3::PrintBridges() const
{
	// если посчитаны мосты в графе
	IF_CALC(SPEC::BRIDGES)
	{
		INFO("печать: список мостов графа");

		std::cout << "Bridges:\n[";
		// печать списка ребер
		PrintEdgeList(*G_MAN_PRES->GetBridges());
		std::cout << "]\n";
	}
}

void PresetScriptManT3::PrintPivots() const
{
	// если посчитаны шарниры в графе
	IF_CALC(SPEC::PIVOT)
	{
		INFO("печать: список шарниров графа");

		std::cout << "Cut vertices:\n[";
		// печать списка шарниров
		PrintPivotsInConsole(*G_MAN_PRES->GetPivots());
		std::cout << "]\n";
	}
}

void PresetScriptManT3::PrintDigraphBridges() const
{
	// если посчитаны мосты в графе
	IF_CALC(SPEC::DIGRAPH_BRIDGES)
	{
		INFO("печать: список мостов орграфа");

		std::cout << "Bridges:\n[";
		// печать списка ребер
		PrintEdgeList(*G_MAN_PRES->GetBridges());
		std::cout << "]\n";
	}
}

void PresetScriptManT3::PrintDigraphPivots() const
{
	// если посчитаны шарниры в графе
	IF_CALC(SPEC::DIGRAPH_PIVOT)
	{
		INFO("печать: список шарниров орграфа");

		std::cout << "Cut vertices:\n[";
		// печать списка шарниров
		PrintPivotsInConsole(*G_MAN_PRES->GetPivots());
		std::cout << "]\n";
	}
}
