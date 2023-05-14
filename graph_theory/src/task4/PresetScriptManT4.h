#ifndef PRESETSCRIPTMANT4_H
#define PRESETSCRIPTMANT4_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT4 :
	virtual public BaseScriptPreset
{
public:

	PresetScriptManT4(const S_PTR(GraphManager)& _graph_man);
	virtual ~PresetScriptManT4() override;

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: ост. дер., крускал
	void PrintMSTCruscal() const;

	// печать: ост. дер., прим
	void PrintMSTPrim() const;

	// печать: ост. дер., борувка
	void PrintMSTBoruvka() const;

	// печать: ост. дер., крускал, прим, борувка
	void PrintMSTCruscalPrimBoruvka() const;


	// печать: ост. дер., орграф, крускал
	void PrintDigraphMSTCruscal() const;
	
	// печать: ост. дер., орграф, прим
	void PrintDigraphMSTPrim() const;

	// печать: ост. дер., орграф, борувка
	void PrintDigraphMSTBoruvka() const;

	// печать: ост. дер., орграф, крускал, прим, борувка
	void PrintDigraphMSTCruscalPrimBoruvka() const;

};


#endif // PRESETSCRIPTMANT4_H
