#include "../pch.h"
#include "PresetScriptManT6.h"


PresetScriptManT6::PresetScriptManT6(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{}


void PresetScriptManT6::PrintDijkstra() const
{
	std::cout << "[===== DIJKSTRA =====]\n";
	std::cout << "Shortest paths lengths:\n";
	PrintShortestPathFromVToAllOtherV(
		G_MAN_PRES->GetDistancies(), m_graph_manager->GetSystemSettings()->m_from
	);
}

void PresetScriptManT6::PrintBellmanFordMur() const
{
	std::cout << "[===== BELLMANFORDMUR =====]\n";
	std::cout << "Shortest paths lengths:\n";
	PrintShortestPathFromVToAllOtherV(
		G_MAN_PRES->GetDistancies(), m_graph_manager->GetSystemSettings()->m_from
	);
}

void PresetScriptManT6::PrintLevit() const
{
	std::cout << "[===== LEVIT =====]\n";
	std::cout << "Shortest paths lengths:\n";
	PrintShortestPathFromVToAllOtherV(
		G_MAN_PRES->GetDistancies(), m_graph_manager->GetSystemSettings()->m_from
	);
}

void PresetScriptManT6::PrintNegativeEdges() const
{
	std::cout << "Graph contains edges with negative weight.\n";
}

void PresetScriptManT6::PrintNoNegativeEdges() const
{
	std::cout << "Graph does not contain edges with negative weight.\n";
}

void PresetScriptManT6::PrintNegativeCycle() const
{
	std::cout << "Graph contains a negative cycle.\n";
}
