#include "../pch.h"
#include "PresetScriptManT10.h"

PresetScriptManT10::PresetScriptManT10(
	const S_PTR(GraphManager)& _graph_man
)
	: BaseScriptPresetManager(_graph_man)
{
}

void PresetScriptManT10::PrintFlow() const
{

}

void PresetScriptManT10::PrintFlowLength() const
{
	std::cout << m_graph_manager->GetMajorPreset()->GetFlowLength()
		<< " - maximum flow from "
		<< m_graph_manager->GetMajorPreset()->GetSource() + 1
		<< " to "
		<< m_graph_manager->GetMajorPreset()->GetSink() + 1
		<< ".\n";

	auto print = [](const EdgeBandwidth& _ed) {
		std::cout << _ed.m_from + 1 << " " << _ed.m_to + 1
			<< " " << _ed.m_weight
			<< "/" << _ed.m_bandwidth << '\n';
	};

	auto flow = m_graph_manager->GetMajorPreset()->GetBandwidth();

	std::for_each(flow.begin(), flow.end(), print);

}
