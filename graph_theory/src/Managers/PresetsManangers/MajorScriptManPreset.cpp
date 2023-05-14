#include "../../pch.h"
#include "MajorScriptManPreset.h"

MajorScriptManPreset::MajorScriptManPreset(
	const S_PTR(GraphManager)& _graph_man,	// управляющий графом
	const S_PTR(SystemSetting)& _setts		// сценарий работы 
) :
	BaseScriptPreset(_graph_man),
	PresetScriptManT1(_graph_man),
	PresetScriptManT2(_graph_man),
	PresetScriptManT3(_graph_man),
	PresetScriptManT4(_graph_man),
	m_sys_settings(_setts)
{
	m_specs =
	{
		// Task 1
		{SPEC::SHORTEST_DIST_MATR,	&PresetScriptManT1::PrintShortestDistMatrix},
		{SPEC::ECCENTR,				&PresetScriptManT1::PrintEccentricity},
		{SPEC::CENTRAL_VERT,		&PresetScriptManT1::PrintCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&PresetScriptManT1::PrintPeripheralVertices},
		{SPEC::RADIUS,				&PresetScriptManT1::PrintRadius},
		{SPEC::DIAMETER,			&PresetScriptManT1::PrintDiameter},
		{SPEC::DEGREES_IN,			&PresetScriptManT1::PrintVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&PresetScriptManT1::PrintVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&PresetScriptManT1::PrintVertexDegreesInOut},

		// Task 2
		{SPEC::IS_CONNECTED,							&PresetScriptManT2::PrintIsConnected},
		{SPEC::IS_NOT_CONNECTED,						&PresetScriptManT2::PrintIsNotConnected},
		{SPEC::CONNECTED_COMPONENTS,					&PresetScriptManT2::PrintConnectedComponents},

		{SPEC::IS_DIGRAPH_CONNECTED,					&PresetScriptManT2::PrintIsDigraphConnected},
		{SPEC::IS_DIGRAPH_NOT_CONNECTED,				&PresetScriptManT2::PrintIsDigraphNotConnected},
		{SPEC::DIGRAPH_WEAKLY_CONNECTED_COMPONENTS,		&PresetScriptManT2::PrintDigraphWeaklyConnectedComponents},
		{SPEC::DIGRAPH_STRONGLY_CONNECTED_COMPONENTS,	&PresetScriptManT2::PrintDigraphStronglyConnectedComponents},
		{SPEC::IS_DIGRAPH_WEAKLY_CONNECTED,				&PresetScriptManT2::PrintIsDigraphWeaklyConnected},
		{SPEC::IS_DIGRAPH_STRONGLY_CONNECTED,			&PresetScriptManT2::PrintIsDigraphStronglyConnected},

		// Task 3
		{SPEC::BRIDGES,			&PresetScriptManT3::PrintBridges},
		{SPEC::DIGRAPH_BRIDGES,	&PresetScriptManT3::PrintDigraphBridges},
		{SPEC::PIVOT,			&PresetScriptManT3::PrintPivots},
		{SPEC::DIGRAPH_PIVOT,	&PresetScriptManT3::PrintDigraphPivots},

		// Task 4
		{SPEC::CRUSCAL,					&PresetScriptManT4::PrintMSTCruscal},
		{SPEC::PRIM,					&PresetScriptManT4::PrintMSTPrim},
		{SPEC::BORUVKA,					&PresetScriptManT4::PrintMSTBoruvka},
		{SPEC::CRUSCAL_PRIM_BORUVKA,	&PresetScriptManT4::PrintMSTCruscalPrimBoruvka},

		{SPEC::DIGRAPH_CRUSCAL,					&PresetScriptManT4::PrintDigraphMSTCruscal},
		{SPEC::DIGRAPH_PRIM,					&PresetScriptManT4::PrintDigraphMSTPrim},
		{SPEC::DIGRAPH_BORUVKA,					&PresetScriptManT4::PrintDigraphMSTBoruvka},
		{SPEC::DIGRAPH_CRUSCAL_PRIM_BORUVKA,	&PresetScriptManT4::PrintDigraphMSTCruscalPrimBoruvka},
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
