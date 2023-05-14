#ifndef PRESETGRAPHMANT4_h
#define PRESETGRAPHMANT4_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT4 :
	virtual public BaseGraphPresetManager
{
protected:
	// остовное дерево для Крускала
	U_PTR(SpanningTree) m_kruskal_spanning_tree;

	// остовное дерево для Прима
	U_PTR(SpanningTree) m_prim_spanning_tree;

	// остовное дерево для Борувки
	U_PTR(SpanningTree) m_boruvka_spanning_tree;

	// время на выполнение алгоритма крускала
	ChronoDurationMcs m_kruskal_time;

	// время на выполнение алгоритма прима
	ChronoDurationMcs m_prim_time;

	// время на выполнение алгоритма борувки
	ChronoDurationMcs m_boruvka_time;

public:
	// конструктор и деструктор
	PresetGraphManT4(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states);
	~PresetGraphManT4() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//
	
	// неориентированный граф
	// расчет: крускал
	bool CalculateKruskal();

	// расчет: прим
	bool CalculatePrim();

	// расчет: борувка
	bool CalculateBoruvka();

	// расчет: все три
	bool CalculateKruskalPrimBoruvka();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: остовное дерево, крускал
	const U_PTR(SpanningTree)& GetKruskalSpanTree() const;

	// получение: остовное дерево, прим
	const U_PTR(SpanningTree)& GetPrimSpanTree() const;

	// получение: остовное дерево, борувка
	const U_PTR(SpanningTree)& GetBoruvkaSpanTree() const;

	// получение: время работы крускала
	const ChronoDurationMcs& GetKruskalTime() const;

	// получение: время работы прима
	const ChronoDurationMcs& GetPrimTime() const;

	// получение: время работы борвуки
	const ChronoDurationMcs& GetBoruvkaTime() const;


};


#endif // !PRESETGRAPHMANT4_h
