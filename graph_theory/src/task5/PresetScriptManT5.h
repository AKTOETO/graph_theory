#ifndef PRESETSCRIPTMANT5_H
#define PRESETSCRIPTMANT5_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT5 :
	virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT5(const S_PTR(GraphManager)& _graph_man);
	virtual ~PresetScriptManT5() override;

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: есть кратчайший путь
	void PrintThereIsShortestPath() const;

	// печать: нет кратчайшего путь
	void PrintThereIsNotShortestPath() const;

	// печать: кратчайший путь
	void PrintShortestPath() const;
};

#endif // PRESETSCRIPTMANT5_H
