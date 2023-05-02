#include "../pch.h"
#include "ScriptPrintManagerT2.h"

ScriptPrintManagerT2::ScriptPrintManagerT2(
	std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script
)
	: BaseScriptPrintManager(_filepath, _in_f_type, _script)
{
	m_specs =
	{
		//{SPEC::SHORTEST_DIST_MATR,	&ScriptPrintManagerT2::PrintShortestDistMatrix},
		//{SPEC::ECCENTR,				&ScriptPrintManagerT2::PrintEccentricity},
		//{SPEC::CENTRAL_VERT,		&ScriptPrintManagerT2::PrintCentralVertices},
		//{SPEC::PERIPHERAL_VERT,		&ScriptPrintManagerT2::PrintPeripheralVertices},
		//{SPEC::RADIUS,				&ScriptPrintManagerT2::PrintRadius},
		//{SPEC::DIAMETER,			&ScriptPrintManagerT2::PrintDiameter},
		//{SPEC::DEGREES_IN,			&ScriptPrintManagerT2::PrintVertexDegreesIn},
		//{SPEC::DEGREES_OUT,			&ScriptPrintManagerT2::PrintVertexDegreesOut},
		//{SPEC::DEGREES_IN_OUT,		&ScriptPrintManagerT2::PrintVertexDegreesInOut},
	};
}

ScriptPrintManagerT2::~ScriptPrintManagerT2()
{
	m_graph_manager.reset();
	m_script.reset();
}

#define IF_CALC(_spec) if((*m_graph_manager->GetStatesOfSpecs())[int(_spec)])

void ScriptPrintManagerT2::PrintIsConnected() const
{
	IF_CALC(SPEC::IS_CONNECTED)
	{
		INFO("печать: граф связен");
		std::cout << "Graph is connected.\n";
	}
}

void ScriptPrintManagerT2::PrintIsNotConnected() const
{
}

void ScriptPrintManagerT2::PrintConnectedComponents() const
{
}

void ScriptPrintManagerT2::PrintIsDigraphConnected() const
{

}

void ScriptPrintManagerT2::PrintIsDigraphNotConnected() const
{
}

void ScriptPrintManagerT2::PrintIsDigraphWeaklyConnected() const
{
}

void ScriptPrintManagerT2::PrintIsDigraphStronglyConnected() const
{
	IF_CALC(SPEC::IS_STRONGLY_CONNECTED)
	{
		INFO("печать: граф сильно связен");
		std::cout << "Digraph is strongly connected.\n";
	}
}

void ScriptPrintManagerT2::PrintStronglyConnectedComponents() const
{
}
