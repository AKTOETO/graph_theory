#include "../../pch.h"
#include "MajorScriptManPreset.h"

MajorScriptManPreset::MajorScriptManPreset(
	const S_PTR(GraphManager)& _graph_man,	// управляющий графом
	const S_PTR(SystemSetting)& _setts		// сценарий работы 
) :
	BaseScriptPresetManager(_graph_man),
	PresetScriptManT1(_graph_man),
	PresetScriptManT2(_graph_man),
	PresetScriptManT3(_graph_man),
	PresetScriptManT4(_graph_man),
	PresetScriptManT5(_graph_man),
	PresetScriptManT6(_graph_man),
	PresetScriptManT7(_graph_man),
	m_sys_settings(_setts)
{
	m_specs =
	{
		// Task 1
		{SPEC::T1_SHORTEST_DIST_MATR,	&PresetScriptManT1::PrintShortestDistMatrix},
		{SPEC::T1_ECCENTR,				&PresetScriptManT1::PrintEccentricity},
		{SPEC::T1_CENTRAL_VERT,			&PresetScriptManT1::PrintCentralVertices},
		{SPEC::T1_PERIPHERAL_VERT,		&PresetScriptManT1::PrintPeripheralVertices},
		{SPEC::T1_RADIUS,				&PresetScriptManT1::PrintRadius},
		{SPEC::T1_DIAMETER,				&PresetScriptManT1::PrintDiameter},
		{SPEC::T1_DEGREES_IN,			&PresetScriptManT1::PrintVertexDegreesIn},
		{SPEC::T1_DEGREES_OUT,			&PresetScriptManT1::PrintVertexDegreesOut},
		{SPEC::T1_DEGREES_IN_OUT,		&PresetScriptManT1::PrintVertexDegreesInOut},

		// Task 2
		{SPEC::T2_IS_CONNECTED,							&PresetScriptManT2::PrintIsConnected},
		{SPEC::T2_IS_NOT_CONNECTED,						&PresetScriptManT2::PrintIsNotConnected},
		{SPEC::T2_CONNECTED_COMPONENTS,					&PresetScriptManT2::PrintConnectedComponents},

		{SPEC::T2_IS_DIGRAPH_CONNECTED,						&PresetScriptManT2::PrintIsDigraphConnected},
		{SPEC::T2_IS_DIGRAPH_NOT_CONNECTED,					&PresetScriptManT2::PrintIsDigraphNotConnected},
		{SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,		&PresetScriptManT2::PrintDigraphWeaklyConnectedComponents},
		{SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,	&PresetScriptManT2::PrintDigraphStronglyConnectedComponents},
		{SPEC::T2_IS_DIGRAPH_WEAKLY_CONNECTED,				&PresetScriptManT2::PrintIsDigraphWeaklyConnected},
		{SPEC::T2_IS_DIGRAPH_STRONGLY_CONNECTED,			&PresetScriptManT2::PrintIsDigraphStronglyConnected},

		// Task 3
		{SPEC::T3_BRIDGES,			&PresetScriptManT3::PrintBridges},
		{SPEC::T3_DIGRAPH_BRIDGES,	&PresetScriptManT3::PrintDigraphBridges},
		{SPEC::T3_PIVOT,			&PresetScriptManT3::PrintPivots},
		{SPEC::T3_DIGRAPH_PIVOT,	&PresetScriptManT3::PrintDigraphPivots},

		// Task 4
		{SPEC::T4_KRUSKAL,					&PresetScriptManT4::PrintMSTKruskal},
		{SPEC::T4_PRIM,						&PresetScriptManT4::PrintMSTPrim},
		{SPEC::T4_BORUVKA,					&PresetScriptManT4::PrintMSTBoruvka},
		{SPEC::T4_KRUSKAL_PRIM_BORUVKA,		&PresetScriptManT4::PrintMSTKruskalPrimBoruvka},

		// Task 5
		{SPEC::T5_THERE_IS_SHORTEST_PATH,			&PresetScriptManT5::PrintThereIsShortestPath},
		{SPEC::T5_THERE_IS_NOT_SHORTEST_PATH,		&PresetScriptManT5::PrintThereIsNotShortestPath},
		{SPEC::T5_DIJKSTRA_PATH,					&PresetScriptManT5::PrintShortestPath},

		// Task 6
		{SPEC::T6_USE_DIJKSTRA,				&PresetScriptManT6::PrintDijkstra},
		{SPEC::T6_USE_BELLMAN_FORD_MUR,		&PresetScriptManT6::PrintBellmanFordMur},
		{SPEC::T6_USE_LEVIT,				&PresetScriptManT6::PrintLevit},
		{SPEC::T6_NO_NEGATIVE_EDGES,		&PresetScriptManT6::PrintNoNegativeEdges},
		{SPEC::T6_NEGATIVE_EDGES,			&PresetScriptManT6::PrintNegativeEdges},
		{SPEC::T6_NEGATIVE_CYCLE,			&PresetScriptManT6::PrintNegativeCycle},

		// Task 7
		{SPEC::T7_USE_JHONSON,				&PresetScriptManT7::PrintJhonson},
		{SPEC::T7_NO_NEGATIVE_EDGES,		&PresetScriptManT7::PrintNoNegativeEdges},
		{SPEC::T7_NEGATIVE_EDGES,			&PresetScriptManT7::PrintNegativeEdges},
		{SPEC::T7_NEGATIVE_CYCLE,			&PresetScriptManT7::PrintNegativeCycle},
		
	};
}

MajorScriptManPreset::~MajorScriptManPreset()
{
	m_sys_settings.reset();
	m_graph_manager.reset();
}

void MajorScriptManPreset::Run()
{
	// расчитываем через управляющего графом все нужные данные
	std::for_each(m_sys_settings->m_script.begin(), m_sys_settings->m_script.end(), [&](const SPEC& spec)
		{
			G_MAN_PRES->CalculateSpecifier(spec);
		}
	);

	// печать расчитанных величин
	std::for_each(m_sys_settings->m_script.begin(), m_sys_settings->m_script.end(), [&](const SPEC& el)
		{
			IF_CALC(el)	(this->*m_specs[el])();
		}
	);
}
