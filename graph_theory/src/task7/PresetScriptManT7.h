#ifndef PRESETSCRIPTMANT7_H
#define PRESETSCRIPTMANT7_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT7 :
    virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT7(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Дейкстра
	void PrintJhonson() const;

	// печать: Нет отрицательных весов
	void PrintNegativeEdges() const;

	// печать: Есть отрицательные веса
	void PrintNoNegativeEdges() const;

	// печать: Отрицательный цикл
	void PrintNegativeCycle() const;

};

#endif // PRESETSCRIPTMANT7_H
