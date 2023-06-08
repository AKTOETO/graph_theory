#ifndef PRESETSCRIPTMANT11_H
#define PRESETSCRIPTMANT11_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT11 :
    virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT11(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Граф двудольный
	void PrintIsBipartite() const;

	// печать: Граф не двудольный
	void PrintIsNotBipartite() const;

	// печать: Паросочетание
	void PrintMatching() const;

};

#endif // PRESETSCRIPTMANT10_H
