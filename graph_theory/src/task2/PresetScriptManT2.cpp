#include "../pch.h"
#include "PresetScriptManT2.h"

PresetScriptManT2::PresetScriptManT2(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPreset(_graph_man)
{}

PresetScriptManT2::~PresetScriptManT2()
{
	m_graph_manager.reset();
}

void PresetScriptManT2::PrintIsConnected() const
{
	INFO("печать: граф связен");

	std::cout << "Graph is connected.\n";
}

void PresetScriptManT2::PrintIsNotConnected() const
{
	INFO("печать: граф не связен");

	std::cout << "Graph is not connected and contains "
		+ std::to_string(G_MAN_PRES->GetNumberOfConnectedComponents())
		+ " connected components.\n";
}

void PresetScriptManT2::PrintConnectedComponents() const
{
	INFO("печать: компоненты связности");

	std::cout << "Connected components:\n";

	// печать компнет связности, используя массив маркированных вершин
	std::cout << "[";
	PrintConnectedComponentsInConsole(*G_MAN_PRES->GetConnectedComponents());
	std::cout << "]\n";
}

void PresetScriptManT2::PrintIsDigraphConnected() const
{
	INFO("печать: граф связен");
	std::cout << "Diraph is connected.\n";
}

void PresetScriptManT2::PrintIsDigraphNotConnected() const
{
	INFO("печать: орграф не связен");
	std::cout << "Digraph is not connected and contains "
		+ std::to_string(G_MAN_PRES->GetNumberOfConnectedComponents())
		+ " connected components.\n";
}

void PresetScriptManT2::PrintIsDigraphWeaklyConnected() const
{
	INFO("печать: орграф слабо связен");
	std::cout << "Digraph is weakly connected and contains "
		+ std::to_string(G_MAN_PRES->GetNumberOfStronglyConnectedComponents())
		+ " strongly connected components.\n";
}

void PresetScriptManT2::PrintIsDigraphStronglyConnected() const
{
	INFO("печать: орграф сильно связен");
	std::cout << "Digraph is strongly connected.\n";

}

void PresetScriptManT2::PrintDigraphStronglyConnectedComponents() const
{
	INFO("печать: компоненты сильной связности");

	std::cout << "Strongly connected components:\n";

	// печать компнет связности, используя массив маркированных вершин
	std::cout << "[";
	PrintConnectedComponentsInConsole(*G_MAN_PRES->GetStronglyConnectedComponents());
	std::cout << "]\n";

}

void PresetScriptManT2::PrintDigraphWeaklyConnectedComponents() const
{

	INFO("печать: компоненты слабой связности");

	std::cout << "Connected components:\n";

	// печать компнет связности, используя массив маркированных вершин
	std::cout << "[";
	PrintConnectedComponentsInConsole(*G_MAN_PRES->GetConnectedComponents());
	std::cout << "]\n";

}
