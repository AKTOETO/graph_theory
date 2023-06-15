#ifndef PRESETSCRIPTMANT9_H
#define PRESETSCRIPTMANT9_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT9 :
    virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT9(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Муравьиная колонпя
	void PrintAntColony() const;

	// печать: Ветви и границы
	void PrintBranchAndBounds() const;

};

#endif // PRESETSCRIPTMANT7_H
