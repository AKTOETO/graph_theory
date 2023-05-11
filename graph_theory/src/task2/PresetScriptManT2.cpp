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
	IF_CALC(SPEC::IS_CONNECTED)
	{
		INFO("печать: граф связен");

		std::cout << "Graph is connected.\n";
	}
}

void PresetScriptManT2::PrintIsNotConnected() const
{
	IF_CALC(SPEC::IS_NOT_CONNECTED)
	{
		INFO("печать: граф не связен");

		std::cout << "Graph is not connected and contains "
			+ std::to_string(G_MAN_PRES->GetNumberOfConnectedComponents())
			+ " connected components.\n";
	}
}

void PresetScriptManT2::PrintConnectedComponents() const
{
	// если были просчитаны компоненты связности для неориентированного графа
	IF_CALC(SPEC::CONNECTED_COMPONENTS)
	{
		INFO("печать: компоненты связности");

		std::cout << "Connected components:\n";

		// печать компнет связности, используя массив маркированных вершин
		std::cout << "[";
		PrintConnectedComponentsInConsole(*G_MAN_PRES->GetConnectedComponents());
		std::cout << "]\n";
	}
}

void PresetScriptManT2::PrintIsDigraphConnected() const
{
	// если орграф связен
	IF_CALC(SPEC::IS_DIGRAPH_CONNECTED)
	{
		INFO("печать: граф связен");
		std::cout << "Diraph is connected.\n";
	}
}

void PresetScriptManT2::PrintIsDigraphNotConnected() const
{
	// если орграф не связен
	IF_CALC(SPEC::IS_DIGRAPH_NOT_CONNECTED)
	{
		INFO("печать: орграф не связен");
		std::cout << "Digraph is not connected and contains "
			+ std::to_string(G_MAN_PRES->GetNumberOfConnectedComponents())
			+ " connected components.\n";
	}
}

void PresetScriptManT2::PrintIsDigraphWeaklyConnected() const
{
	// если орграф слабо связен
	IF_CALC(SPEC::IS_DIGRAPH_WEAKLY_CONNECTED)
	{
		INFO("печать: орграф слабо связен");
		std::cout << "Digraph is weakly connected and contains "
			+ std::to_string(G_MAN_PRES->GetNumberOfStronglyConnectedComponents())
			+ " strongly connected components.\n";
	}
}

void PresetScriptManT2::PrintIsDigraphStronglyConnected() const
{
	IF_CALC(SPEC::IS_DIGRAPH_STRONGLY_CONNECTED)
	{
		INFO("печать: орграф сильно связен");
		std::cout << "Digraph is strongly connected.\n";
	}
}

void PresetScriptManT2::PrintDigraphStronglyConnectedComponents() const
{
	// если были просчитаны компоненты сильной связности
	IF_CALC(SPEC::DIGRAPH_STRONGLY_CONNECTED_COMPONENTS)
	{
		INFO("печать: компоненты сильной связности");

		std::cout << "Strongly connected components:\n";

		// печать компнет связности, используя массив маркированных вершин
		std::cout << "[";
		PrintConnectedComponentsInConsole(*G_MAN_PRES->GetStronglyConnectedComponents());
		std::cout << "]\n";
	}
}

void PresetScriptManT2::PrintDigraphWeaklyConnectedComponents() const
{
	// если были просчитаны компоненты слабой связности для орграфа
	IF_CALC(SPEC::DIGRAPH_WEAKLY_CONNECTED_COMPONENTS)
	{
		INFO("печать: компоненты слабой связности");

		std::cout << "Connected components:\n";

		// печать компнет связности, используя массив маркированных вершин
		std::cout << "[";
		PrintConnectedComponentsInConsole(*G_MAN_PRES->GetConnectedComponents());
		std::cout << "]\n";
	}
}
