#pragma once
#include "../Managers/GraphManager.h"

class BaseScriptPreset
{
protected:
	// Управляющий графом
	S_PTR(GraphManager) m_graph_manager;

public:
	BaseScriptPreset(const S_PTR(GraphManager)& _graph_man)
		:m_graph_manager(_graph_man)
	{};


	virtual ~BaseScriptPreset()
	{
		m_graph_manager.reset();
	};
};

#define G_MAN_PRES m_graph_manager->GetMajorPreset()
#define IF_CALC(_spec) if((*G_MAN_PRES->GetStatesOfSpecs())[int(_spec)])
