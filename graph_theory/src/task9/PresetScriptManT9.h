#ifndef PRESETSCRIPTMANT8_H
#define PRESETSCRIPTMANT8_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT8 :
    virtual public BaseScriptPresetManager
{
protected:
	Params m_heur_names;

public:

	PresetScriptManT8(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Кратчайший путь
	void PrintPath() const;

	// печать: Длина пути
	void PrintPathLength() const;

};

#endif // PRESETSCRIPTMANT7_H
