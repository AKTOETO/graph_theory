#ifndef PRESETSCRIPTMANT4_H
#define PRESETSCRIPTMANT4_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT4 :
	virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT4(const S_PTR(GraphManager)& _graph_man);
	virtual ~PresetScriptManT4() override;

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: ост. дер., крускал
	void PrintMSTKruskal() const;

	// печать: ост. дер., прим
	void PrintMSTPrim() const;

	// печать: ост. дер., борувка
	void PrintMSTBoruvka() const;

	// печать: ост. дер., крускал, прим, борувка
	void PrintMSTKruskalPrimBoruvka() const;

};


#endif // PRESETSCRIPTMANT4_H
