#include "../pch.h"
#include "PresetScriptManT5.h"

PresetScriptManT5::PresetScriptManT5(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{}

PresetScriptManT5::~PresetScriptManT5()
{
}

void PresetScriptManT5::PrintThereIsShortestPath() const
{
	std::cout << "Shortest path length between "
		<< m_graph_manager->GetSystemSettings()->m_from + 1
		<< " and "
		<< m_graph_manager->GetSystemSettings()->m_to + 1
		<< " vertices: " <<
		G_MAN_PRES->GetShortestDistToVert()
		<< "\n";
}

void PresetScriptManT5::PrintThereIsNotShortestPath() const
{
	std::cout << "There is no path between the vertices "
		<< m_graph_manager->GetSystemSettings()->m_from + 1
		<< " and "
		<< m_graph_manager->GetSystemSettings()->m_to + 1
		<< "\n";
}

void PresetScriptManT5::PrintShortestPath() const
{
	if(G_MAN_PRES->GetShortestDistToVert() != INF)
	{
		std::cout << "Path:\n[";
		PrintEdgeList(G_MAN_PRES->GetShortestDistEdgeList(), ", ", 1);
		std::cout << "]\n";
	}
}
