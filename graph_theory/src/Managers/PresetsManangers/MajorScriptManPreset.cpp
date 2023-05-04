#include "../../pch.h"
#include "MajorScriptManPreset.h"

MajorScriptManPreset::MajorScriptManPreset(
	//std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script
	const S_PTR(GraphManager)& _graph_man, const S_PTR(Script)& _script
) :
	BaseScriptPreset(_graph_man),
	PresetScriptManrT1(_graph_man),
	PresetScriptManrT2(_graph_man),
	m_script(_script)
{
	m_specs =
	{
		// Task 1
		{SPEC::SHORTEST_DIST_MATR,	&PresetScriptManrT1::PrintShortestDistMatrix},
		{SPEC::ECCENTR,				&PresetScriptManrT1::PrintEccentricity},
		{SPEC::CENTRAL_VERT,		&PresetScriptManrT1::PrintCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&PresetScriptManrT1::PrintPeripheralVertices},
		{SPEC::RADIUS,				&PresetScriptManrT1::PrintRadius},
		{SPEC::DIAMETER,			&PresetScriptManrT1::PrintDiameter},
		{SPEC::DEGREES_IN,			&PresetScriptManrT1::PrintVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&PresetScriptManrT1::PrintVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&PresetScriptManrT1::PrintVertexDegreesInOut},

		// Task 2
		//{SPEC::SHORTEST_DIST_MATR,	&PresetScriptManrT2::  },
		//{SPEC::ECCENTR,				&PresetScriptManrT2::  },
		//{SPEC::CENTRAL_VERT,			&PresetScriptManrT2::  },
		//{SPEC::PERIPHERAL_VERT,		&PresetScriptManrT2::  },
		//{SPEC::RADIUS,				&PresetScriptManrT2::  },
		//{SPEC::DIAMETER,				&PresetScriptManrT2::  },
		//{SPEC::DEGREES_IN,			&PresetScriptManrT2::  },
		//{SPEC::DEGREES_OUT,			&PresetScriptManrT2::  },
		//{SPEC::DEGREES_IN_OUT,		&PresetScriptManrT2::  },

	};
}

MajorScriptManPreset::~MajorScriptManPreset()
{
	m_script.reset();
	m_graph_manager.reset();
}

void MajorScriptManPreset::Run()
{
	std::for_each(m_script->begin(), m_script->end(), [&](const SPEC& spec)
		{
			G_MAN_PRES->CalculateSpecifier(spec);
		}
	);

	// TODO надо еще выводить величины
	// для вывода спрашивать у граф менеджера: 
	// расчитана ли эта велечина?
	// для всего сценария вызываем соответствующие функции печати
	std::for_each(m_script->begin(), m_script->end(), [&](const SPEC& el)
		{
			(this->*m_specs[el])();
		}
	);
}
