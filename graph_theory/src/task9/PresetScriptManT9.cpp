﻿#include "../pch.h"
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
//
//void PresetScriptManT8::PrintPath() const
//{
//	// получене кратчайшийх расстояний для всех эвристик
//	std::vector<S_PTR(CellVector)> dist = G_MAN_PRES->GetAStarShortestPath();
//
//	// получение длин кратчайших расстояний
//	WeightVector len = G_MAN_PRES->GetAStarShortestPathLength();
//
//	// получаем пройденные клетки каждым алгоритмом
//	std::vector<double> used = G_MAN_PRES->GetAStarPercentUsedCells();
//
//	for (int i = 0; i < m_heur_names.size(); i++)
//	{
//		std::cout << '\n' << m_heur_names[i] << '\n';
//
//		// Длина пути
//		std::cout << len[i] << " - length of path between "
//			<< m_graph_manager->GetSystemSettings()->m_begin
//			<< " and "
//			<< m_graph_manager->GetSystemSettings()->m_end
//			<< " points.\n";
//
//		// процент просмотренных клеток
//		std::cout << "Percentage of used cells: "
//			<< std::fixed << std::setprecision(1) << used[i] << "%\n";
//
//		// печатаем вектор расстояний
//		std::cout << "Path:\n[";
//		PrintCellVector((*dist[i]));
//		std::cout << "]\n";
//
//	}
//}
//
//void PresetScriptManT8::PrintPathLength() const
//{
//}
