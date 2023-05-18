#include "../pch.h"
#include "PresetScriptManT7.h"


PresetScriptManT7::PresetScriptManT7(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{}


void PresetScriptManT7::PrintJhonson() const
{
	std::cout << "[===== JHONSON =====]\n";
	std::cout << "Shortest paths lengths:\n";
	PrintAllShortestPath(
		G_MAN_PRES->GetJhonsonDistancies(), 0
	);
}

void PresetScriptManT7::PrintNegativeEdges() const
{
	std::cout << "Graph contains edges with negative weight.\n";
}

void PresetScriptManT7::PrintNoNegativeEdges() const
{
	std::cout << "Graph does not contain edges with negative weight.\n";
}

void PresetScriptManT7::PrintNegativeCycle() const
{
	std::cout << "Graph contains a negative cycle.\n";
}
