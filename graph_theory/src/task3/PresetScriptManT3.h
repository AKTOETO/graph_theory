#ifndef PRESETSCRIPTMANT3_H
#define PRESETSCRIPTMANT3_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT3
	: virtual public BaseScriptPreset
{
public:

	PresetScriptManT3(const S_PTR(GraphManager)& _graph_man);
	virtual ~PresetScriptManT3() override;

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: мосты графа
	void PrintBridges() const;

	// печать: шарниры графа
	void PrintPivots() const;

	// печать: мосты орграфа
	void PrintDigraphBridges() const;

	// печать: шарниры орграфа
	void PrintDigraphPivots() const;
};

#endif // PRESETSCRIPTMANT3_H
