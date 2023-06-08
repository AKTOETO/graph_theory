#include "../pch.h"
#include "PresetScriptManT11.h"

PresetScriptManT11::PresetScriptManT11(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{
}

void PresetScriptManT11::PrintIsBipartite() const
{
	std::cout << "Graph is bipartite. Number of Edges: "
		<<G_MAN_PRES->GetEdgeNumber()<<'\n';
}

void PresetScriptManT11::PrintIsNotBipartite() const
{
	std::cout << "Graph is not bipartite.\n";
}

void PresetScriptManT11::PrintMatching() const
{
	std::cout << "Matching:\n";
	auto lst = G_MAN_PRES->GetMatching();
	std::for_each(lst.begin(), lst.end(), [](const Edge& _ed)
		{
			std::cout << _ed.m_from << " - " << _ed.m_to << '\n';
		});
}

