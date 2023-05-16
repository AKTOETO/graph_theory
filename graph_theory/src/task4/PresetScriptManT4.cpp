#include "../pch.h"
#include "PresetScriptManT4.h"

PresetScriptManT4::PresetScriptManT4(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{}

PresetScriptManT4::~PresetScriptManT4()
{
	m_graph_manager.reset();
}

//===================================//
// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
//===================================//

void PresetScriptManT4::PrintMSTKruskal() const
{
	std::cout << "Minimum spanning tree:\n";
	std::cout << "[";
	PrintEdgeList(G_MAN_PRES->GetKruskalSpanTree()->m_edge_list, ", ", 1);
	std::cout << "]\nWeight of spanning tree: "
		<< G_MAN_PRES->GetKruskalSpanTree()->m_weight
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
	std::cout << "Minimum spanning tree:\n";
	std::cout << "[";
	PrintEdgeList(G_MAN_PRES->GetBoruvkaSpanTree()->m_edge_list, ", ", 1);
	std::cout << "]\nWeight of spanning tree: "
		<< G_MAN_PRES->GetBoruvkaSpanTree()->m_weight
		<< std::endl;
}

void PresetScriptManT4::PrintMSTKruskalPrimBoruvka() const
{
	std::cout.clear();

	std::cout << "[===== CRUSCAL =====]\n";
	PrintMSTKruskal();
	std::cout << "Execution time (mcs): " << G_MAN_PRES->GetKruskalTime().count() << "\n";
	std::cout << "Execution time (ms): " <<
		std::chrono::duration_cast<ms>(G_MAN_PRES->GetKruskalTime()).count() << "\n\n";

	std::cout << "[====== PRIM ======]\n";
	PrintMSTPrim();
	std::cout << "Execution time (mcs): " << G_MAN_PRES->GetPrimTime().count() << "\n";
	std::cout << "Execution time (ms): " <<
		std::chrono::duration_cast<ms>(G_MAN_PRES->GetPrimTime()).count() << "\n\n";

	std::cout << "[===== BORUVKA =====]\n";
	PrintMSTBoruvka();
	std::cout << "Execution time (mcs): " << G_MAN_PRES->GetBoruvkaTime().count() << "\n";
	std::cout << "Execution time (ms): " <<
		std::chrono::duration_cast<ms>(G_MAN_PRES->GetBoruvkaTime()).count() << "\n\n";
}
