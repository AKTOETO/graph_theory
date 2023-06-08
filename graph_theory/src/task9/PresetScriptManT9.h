#ifndef PRESETSCRIPTMANT9_H
#define PRESETSCRIPTMANT9_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT9 :
    virtual public BaseScriptPresetManager
{
protected:
	Params m_heur_names;

public:

	PresetScriptManT9(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Гамильтонов цикл. Муравьиная колония
	void PrintAntColonyPath() const;

	// печать: Гамильтонов цикл. Ветви и границы
	void PrintBranchAndBoundsPath() const;

};

#endif // PRESETSCRIPTMANT7_H
