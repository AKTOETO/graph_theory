#include "../pch.h"
#include "PresetScriptManT2.h"

PresetScriptManrT2::PresetScriptManrT2(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPreset(_graph_man)
{
	//m_specs =
	//{
	//	//{SPEC::SHORTEST_DIST_MATR,	&ScriptPrintManagerT2::PrintShortestDistMatrix},
	//	//{SPEC::ECCENTR,				&ScriptPrintManagerT2::PrintEccentricity},
	//	//{SPEC::CENTRAL_VERT,		&ScriptPrintManagerT2::PrintCentralVertices},
	//	//{SPEC::PERIPHERAL_VERT,		&ScriptPrintManagerT2::PrintPeripheralVertices},
	//	//{SPEC::RADIUS,				&ScriptPrintManagerT2::PrintRadius},
	//	//{SPEC::DIAMETER,			&ScriptPrintManagerT2::PrintDiameter},
	//	//{SPEC::DEGREES_IN,			&ScriptPrintManagerT2::PrintVertexDegreesIn},
	//	//{SPEC::DEGREES_OUT,			&ScriptPrintManagerT2::PrintVertexDegreesOut},
	//	//{SPEC::DEGREES_IN_OUT,		&ScriptPrintManagerT2::PrintVertexDegreesInOut},
	//};
}

PresetScriptManrT2::~PresetScriptManrT2()
{
	m_graph_manager.reset();
}

//#define IF_CALC(_spec) if((*m_graph_manager->GetStatesOfSpecs())[int(_spec)])

void PresetScriptManrT2::PrintIsConnected() const
{
	IF_CALC(SPEC::IS_CONNECTED)
	{
		INFO("печать: граф связен");
		std::cout << "Graph is connected.\n";
	}
}

void PresetScriptManrT2::PrintIsNotConnected() const
{
}

void PresetScriptManrT2::PrintConnectedComponents() const
{
}

void PresetScriptManrT2::PrintIsDigraphConnected() const
{

}

void PresetScriptManrT2::PrintIsDigraphNotConnected() const
{
}

void PresetScriptManrT2::PrintIsDigraphWeaklyConnected() const
{
}

void PresetScriptManrT2::PrintIsDigraphStronglyConnected() const
{
	IF_CALC(SPEC::IS_STRONGLY_CONNECTED)
	{
		INFO("печать: граф сильно связен");
		std::cout << "Digraph is strongly connected.\n";
	}
}

void PresetScriptManrT2::PrintStronglyConnectedComponents() const
{
}
