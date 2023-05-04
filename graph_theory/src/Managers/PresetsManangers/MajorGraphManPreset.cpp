#include "../../pch.h"
#include "MajorGraphManPreset.h"

MajorGraphManPreset::MajorGraphManPreset(
	const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states)
	:BaseGraphManager(_graph, _states), 

	PresetGraphManT1(_graph, _states),
	PresetGraphManT2(_graph, _states)
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

const S_PTR(std::vector<bool>)& MajorGraphManPreset::GetStatesOfSpecs() const
{
	return m_state_of_spec;
}
