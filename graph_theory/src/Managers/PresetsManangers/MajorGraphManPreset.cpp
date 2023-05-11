#include "../../pch.h"
#include "MajorGraphManPreset.h"

MajorGraphManPreset::MajorGraphManPreset(
	const S_PTR(Graph)& _graph, const S_PTR(State) _states)
	:BaseGraphManager(_graph, _states),

	PresetGraphManT1(_graph, _states),
	PresetGraphManT2(_graph, _states),
	PresetGraphManT3(_graph, _states)
{
	m_specs =
	{
		// Task 1
		{SPEC::SHORTEST_DIST_MATR,	&PresetGraphManT1::CalculateShortestDistMatr},
		{SPEC::ECCENTR,				&PresetGraphManT1::CalculateEccentricity},
		{SPEC::CENTRAL_VERT,		&PresetGraphManT1::CalculateCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&PresetGraphManT1::CalculatePeripheralVertices},
		{SPEC::RADIUS,				&PresetGraphManT1::CalculateRadius},
		{SPEC::DIAMETER,			&PresetGraphManT1::CalculateDiameter},
		{SPEC::DEGREES_IN,			&PresetGraphManT1::CalculateVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&PresetGraphManT1::CalculateVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&PresetGraphManT1::CalculateVertexDegreesInOut},

		// Task 2
		{SPEC::IS_CONNECTED,							&PresetGraphManT2::CalculateIsConnected},
		{SPEC::IS_NOT_CONNECTED,						&PresetGraphManT2::CalculateIsNotConnected},
		{SPEC::CONNECTED_COMPONENTS,					&PresetGraphManT2::CalculateConnectedComponents},
		{SPEC::DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,		&PresetGraphManT2::CalculateDWeaklyConnectedComponents},
		{SPEC::IS_DIGRAPH_CONNECTED,					&PresetGraphManT2::CalculateIsDigraphConnected},
		{SPEC::IS_DIGRAPH_NOT_CONNECTED,				&PresetGraphManT2::CalculateIsDigraphNotConnected},
		{SPEC::IS_DIGRAPH_WEAKLY_CONNECTED,				&PresetGraphManT2::CalculateIsDigraphWeaklyConnected},
		{SPEC::IS_DIGRAPH_STRONGLY_CONNECTED,			&PresetGraphManT2::CalculateIsDigraphStronglyConnected},
		{SPEC::DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,	&PresetGraphManT2::CalculateDStronglyConnectedComponents},

		// Task3
		{SPEC::BRIDGES,			&PresetGraphManT3::CalculateBridges},
		{SPEC::DIGRAPH_BRIDGES,	&PresetGraphManT3::CalculateDigraphBridges},
		{SPEC::PIVOT,			&PresetGraphManT3::CalculatePivots},
		{SPEC::DIGRAPH_PIVOT,	&PresetGraphManT3::CalculateDigraphPivots},

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

const S_PTR(State)& MajorGraphManPreset::GetStatesOfSpecs() const
{
	return m_state_of_spec;
}
