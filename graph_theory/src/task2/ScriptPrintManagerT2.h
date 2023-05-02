#pragma once
#include "GraphManagerT2.h"
#include "../BaseScriptPrintManager.hpp"

class ScriptPrintManagerT2 : public BaseScriptPrintManager<ScriptPrintManagerT2, GraphManagerT2>
{
public:
	ScriptPrintManagerT2(std::string _filepath, INPUT_FILE_TYPE, Script);
	virtual ~ScriptPrintManagerT2() override;

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

	// печать: слабо ли свзяен диграф
	void PrintIsDigraphWeaklyConnected() const;
	
	// печать: сильно ли свзяен диграф
	void PrintIsDigraphStronglyConnected() const;

	// печать: компоненты сильной связности
	void PrintStronglyConnectedComponents() const;

};

