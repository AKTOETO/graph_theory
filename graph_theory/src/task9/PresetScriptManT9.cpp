#include "../pch.h"
#include "PresetScriptManT9.h"

PresetScriptManT9::PresetScriptManT9(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{
}

void PresetScriptManT9::PrintAntColony() const
{
	std::cout << "Hamiltonian cycle has length "
		<< G_MAN_PRES->GetHamiltonCyclesLengthAnt()
		<< ".\n";
	PrintEdgeListVertically(*G_MAN_PRES->GetMinHamiltonCycleAnt(), " - ", 1, " : ");
}

void PresetScriptManT9::PrintBranchAndBounds() const
{
}
