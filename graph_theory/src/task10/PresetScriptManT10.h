#ifndef PRESETSCRIPTMANT10_H
#define PRESETSCRIPTMANT10_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT10 :
    virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT10(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Поток
	void PrintFlow() const;

	// печать: Длина потока
	void PrintFlowLength() const;

};

#endif // PRESETSCRIPTMANT10_H
