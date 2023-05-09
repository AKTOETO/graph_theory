#ifndef PRESETSCRIPTMANT2_H
#define PRESETSCRIPTMANT2_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManrT2 : virtual public BaseScriptPreset
{
public:

	PresetScriptManrT2(const S_PTR(GraphManager)& _graph_man);
	virtual ~PresetScriptManrT2() override;

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: связен ли граф
	void PrintIsConnected() const;

	// печать: не связен ли граф
	void PrintIsNotConnected() const;

	// печать: компоненты связности
	void PrintConnectedComponents() const;

	// печать: связен ли диграф
	void PrintIsDigraphConnected() const;

	// печать: не связен ли диграф
	void PrintIsDigraphNotConnected() const;

	// печать: слабо ли связен диграф
	void PrintIsDigraphWeaklyConnected() const;
	
	// печать: сильно ли связен диграф
	void PrintIsDigraphStronglyConnected() const;

	// печать: компоненты сильной связности
	void PrintDigraphStronglyConnectedComponents() const;

	// печать: компоненты слабой связности
	void PrintDigraphWeaklyConnectedComponents() const;

};

#endif // PRESETSCRIPTMANT2_H
