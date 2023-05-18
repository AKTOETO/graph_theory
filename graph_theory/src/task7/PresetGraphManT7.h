#ifndef PRESETGRAPHMANT7_h
#define PRESETGRAPHMANT7_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT7 :
    virtual public BaseGraphPresetManager
{
protected:

	// есть ли отрицательный цикл
	bool m_is_there_negative_cycle;

	// есть ли отрицательные ребра
	bool m_is_there_negative_edges;

	// список путей от заданной вершины до всех остальных
	U_PTR(VertexMatrix) m_dist;

public:
	// конструктор и деструктор
	PresetGraphManT7(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT7() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: Джонсон
	bool CalculateJhonsonShortPath();

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

	// получение: список путей от всех вершин до всех остальных
	const VertexMatrix& GetJhonsonDistancies() const;
};

#endif // !PRESETGRAPHMANT6_h
