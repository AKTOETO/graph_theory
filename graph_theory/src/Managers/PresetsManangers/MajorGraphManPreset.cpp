#include "../../pch.h"
#include "MajorGraphManPreset.h"

MajorGraphManPreset::MajorGraphManPreset(
	const S_PTR(SystemSetting)& _settings, const S_PTR(Graph)& _graph, const S_PTR(StateVector) _states)
	:BaseGraphPresetManager(_settings, _graph, _states),

	PresetGraphManT1(_settings, _graph, _states),
	PresetGraphManT2(_settings, _graph, _states),
	PresetGraphManT3(_settings, _graph, _states),
	PresetGraphManT4(_settings, _graph, _states),
	PresetGraphManT5(_settings, _graph, _states),
	PresetGraphManT6(_settings, _graph, _states),
	PresetGraphManT7(_settings, _graph, _states),
	PresetGraphManT8(_settings, _graph, _states),
	PresetGraphManT9(_settings, _graph, _states)
{
	m_specs =
	{
		// Task 1
		{SPEC::T1_SHORTEST_DIST_MATR,	&PresetGraphManT1::CalculateShortestDistMatr},
		{SPEC::T1_ECCENTR,				&PresetGraphManT1::CalculateEccentricity},
		{SPEC::T1_CENTRAL_VERT,			&PresetGraphManT1::CalculateCentralVertices},
		{SPEC::T1_PERIPHERAL_VERT,		&PresetGraphManT1::CalculatePeripheralVertices},
		{SPEC::T1_RADIUS,				&PresetGraphManT1::CalculateRadius},
		{SPEC::T1_DIAMETER,				&PresetGraphManT1::CalculateDiameter},
		{SPEC::T1_DEGREES_IN,			&PresetGraphManT1::CalculateVertexDegreesIn},
		{SPEC::T1_DEGREES_OUT,			&PresetGraphManT1::CalculateVertexDegreesOut},
		{SPEC::T1_DEGREES_IN_OUT,		&PresetGraphManT1::CalculateVertexDegreesInOut},

		// Task 2
		{SPEC::T2_IS_CONNECTED,								&PresetGraphManT2::CalculateIsConnected},
		{SPEC::T2_IS_NOT_CONNECTED,							&PresetGraphManT2::CalculateIsNotConnected},
		{SPEC::T2_CONNECTED_COMPONENTS,						&PresetGraphManT2::CalculateConnectedComponents},
		{SPEC::T2_DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,		&PresetGraphManT2::CalculateDWeaklyConnectedComponents},
		{SPEC::T2_IS_DIGRAPH_CONNECTED,						&PresetGraphManT2::CalculateIsDigraphConnected},
		{SPEC::T2_IS_DIGRAPH_NOT_CONNECTED,					&PresetGraphManT2::CalculateIsDigraphNotConnected},
		{SPEC::T2_IS_DIGRAPH_WEAKLY_CONNECTED,				&PresetGraphManT2::CalculateIsDigraphWeaklyConnected},
		{SPEC::T2_IS_DIGRAPH_STRONGLY_CONNECTED,			&PresetGraphManT2::CalculateIsDigraphStronglyConnected},
		{SPEC::T2_DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,	&PresetGraphManT2::CalculateDStronglyConnectedComponents},

		// Task 3
		{SPEC::T3_BRIDGES,			&PresetGraphManT3::CalculateBridges},
		{SPEC::T3_DIGRAPH_BRIDGES,	&PresetGraphManT3::CalculateDigraphBridges},
		{SPEC::T3_PIVOT,			&PresetGraphManT3::CalculatePivots},
		{SPEC::T3_DIGRAPH_PIVOT,	&PresetGraphManT3::CalculateDigraphPivots},

		// Task 4
		{SPEC::T4_KRUSKAL,					&PresetGraphManT4::CalculateKruskal},
		{SPEC::T4_PRIM,						&PresetGraphManT4::CalculatePrim},
		{SPEC::T4_BORUVKA,					&PresetGraphManT4::CalculateBoruvka},
		{SPEC::T4_KRUSKAL_PRIM_BORUVKA,		&PresetGraphManT4::CalculateKruskalPrimBoruvka},

		// Task 5
		{SPEC::T5_THERE_IS_SHORTEST_PATH,		&PresetGraphManT5::CalculateThereIsShortestPath},
		{SPEC::T5_THERE_IS_NOT_SHORTEST_PATH,	&PresetGraphManT5::CalculateThereIsNotShortestPath},
		{SPEC::T5_DIJKSTRA_PATH,				&PresetGraphManT5::CalculateShortPathDijkstra},

		// Task 6
		{SPEC::T6_USE_DIJKSTRA,				&PresetGraphManT6::CalculateDijkstraShortPath},
		{SPEC::T6_USE_BELLMAN_FORD_MUR,		&PresetGraphManT6::CalculateBellmanFordMurShortPath},
		{SPEC::T6_USE_LEVIT,				&PresetGraphManT6::CalculateLevitShortPath},
		{SPEC::T6_NO_NEGATIVE_EDGES,		&PresetGraphManT6::CalculateIsThereNoNegativeEdges},
		{SPEC::T6_NEGATIVE_EDGES,			&PresetGraphManT6::CalculateIsThereNegativeEdges},
		{SPEC::T6_NEGATIVE_CYCLE,			&PresetGraphManT6::CalculaetNegativeCycle},

		// Task 7
		{SPEC::T7_USE_JHONSON,				&PresetGraphManT7::CalculateJhonsonShortPath},
		{SPEC::T7_NO_NEGATIVE_EDGES,		&PresetGraphManT7::CalculateIsThereNoNegativeEdges},
		{SPEC::T7_NEGATIVE_EDGES,			&PresetGraphManT7::CalculateIsThereNegativeEdges},
		{SPEC::T7_NEGATIVE_CYCLE,			&PresetGraphManT7::CalculaetNegativeCycle},

		// Task 8
		{SPEC::T8_PATH,				&PresetGraphManT8::CalculateAStarShortestPath},
		{SPEC::T8_PATH_LENGTH,		&PresetGraphManT8::CalculateAStarShortestPathLength},

		// Task 9
		{SPEC::T9_ANT_COLONY,			&PresetGraphManT9::CalculateAntColony},
		{SPEC::T9_BRANCH_AND_BOUND,		&PresetGraphManT9::CalculateBranchAndBounds},
	};
}

MajorGraphManPreset::~MajorGraphManPreset()
{
	m_state_of_spec.reset();
	m_graph.reset();
}

void MajorGraphManPreset::CalculateSpecifier(SPEC _spec)
{
	// если раньше не рассчитывали параметр _spec
	if (!(*m_state_of_spec)[int(_spec)])
	{
		// расчитываем его
		SetStateOfSpec(_spec, (this->*m_specs[_spec])());
	}
}

const S_PTR(StateVector)& MajorGraphManPreset::GetStatesOfSpecs() const
{
	return m_state_of_spec;
}
