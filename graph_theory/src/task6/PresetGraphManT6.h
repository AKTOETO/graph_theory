#ifndef PRESETGRAPHMANT6_h
#define PRESETGRAPHMANT6_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT6 :
    virtual public BaseGraphPresetManager
{
protected:

	// есть ли отрицательный цикл
	bool m_is_there_negative_cycle;

	// есть ли отрицательные ребра
	bool m_is_there_negative_edges;

	// список путей от заданной вершины до всех остальных
	U_PTR(VertexArr) m_dist;

public:
	// конструктор и деструктор
	PresetGraphManT6(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT6() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: Дейкстра
	bool CalculateDijkstraShortPath();

	// расчет: Беллмана-Форда-Мура
	bool CalculateBellmanFordMurShortPath();

	// расчет: Левит
	bool CalculateLevitShortPath();

	// расчет: есть ли отрицательные ребра
	bool CalculateIsThereNegativeEdges();

	// расчет: нет ли отрицательных ребер
	bool CalculateIsThereNoNegativeEdges();

	// расчет: есть ли отрицательный цикл
	bool CalculaetNegativeCycle();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: есть ли отрицательные ребра
	const bool& GetIsThereNegativeEdges() const;

	// получение: есть ли отрицательный цикл
	const bool& GetIsThereNegativeCycle() const;

	// получение: список путей от заданной вершины до всех остальных
	const VertexArr& GetDistancies() const;
};

#endif // !PRESETGRAPHMANT6_h
