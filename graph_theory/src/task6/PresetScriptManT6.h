#ifndef PRESETSCRIPTMANT6_H
#define PRESETSCRIPTMANT6_H

#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT6 :
    virtual public BaseScriptPresetManager
{
public:

	PresetScriptManT6(const S_PTR(GraphManager)& _graph_man);

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать: Дейкстра
	void PrintDijkstra() const;

	// печать: Беллман Форд Мур
	void PrintBellmanFordMur() const;

	// печать: Левит
	void PrintLevit() const;

	// печать: Нет отрицательных весов
	void PrintNegativeEdges() const;

	// печать: Есть отрицательные веса
	void PrintNoNegativeEdges() const;

	// печать: Отрицательный цикл
	void PrintNegativeCycle() const;

};

#endif // PRESETSCRIPTMANT6_H
