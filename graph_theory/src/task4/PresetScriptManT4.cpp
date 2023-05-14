#include "../pch.h"
#include "PresetScriptManT4.h"

PresetScriptManT4::PresetScriptManT4(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPreset(_graph_man)
{}

PresetScriptManT4::~PresetScriptManT4()
{
	m_graph_manager.reset();
}

//===================================//
// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
//===================================//

void PresetScriptManT4::PrintMSTCruscal() const
{
	std::cout << "Minimum spanning tree:\n";
	std::cout << "[";
	PrintEdgeList(G_MAN_PRES->GetCruscalSpanTree()->m_edge_list, ", ", 1);
	std::cout << "]\nWeight of spanning tree: "
		<< G_MAN_PRES->GetCruscalSpanTree()->m_weight
		<< std::endl;
}

void PresetScriptManT4::PrintMSTPrim() const
{
	std::cout << "Minimum spanning tree:\n";
	std::cout << "[";
	PrintEdgeList(G_MAN_PRES->GetPrimSpanTree()->m_edge_list, ", ", 1);
	std::cout << "]\nWeight of spanning tree: "
		<< G_MAN_PRES->GetPrimSpanTree()->m_weight
		<< std::endl;
}

void PresetScriptManT4::PrintMSTBoruvka() const
{
}

void PresetScriptManT4::PrintMSTCruscalPrimBoruvka() const
{
}

void PresetScriptManT4::PrintDigraphMSTCruscal() const
{
}

void PresetScriptManT4::PrintDigraphMSTPrim() const
{
}

void PresetScriptManT4::PrintDigraphMSTBoruvka() const
{
}

void PresetScriptManT4::PrintDigraphMSTCruscalPrimBoruvka() const
{
}
