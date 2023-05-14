#ifndef PRESETGRAPHMANT4_h
#define PRESETGRAPHMANT4_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT4 :
	virtual public BaseGraphPresetManager
{
protected:
	// остовное дерево для Крускала
	U_PTR(SpanningTree) m_cruscal_spanning_tree;

	// остовное дерево для Прима
	U_PTR(SpanningTree) m_prim_spanning_tree;

	// остовное дерево для Борувки
	U_PTR(SpanningTree) m_boruvka_spanning_tree;

public:
	// конструктор и деструктор
	PresetGraphManT4(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states);
	~PresetGraphManT4() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//
	
	// неориентированный граф
	// расчет: крускал
	bool CalculateCruscal();

	// расчет: прим
	bool CalculatePrim();

	// расчет: борувка
	bool CalculateBoruvka();

	// расчет: все три
	bool CalculateCruscalPrimBoruvka();

	// ориентированный граф
	// расчет ограф: крускал
	bool CalculateDigraphCruscal();

	// расчет ограф: прим
	bool CalculateDigraphPrim();

	// расчет ограф: борувка
	bool CalculateDigraphBoruvka();

	// расчет ограф: все три
	bool CalculateDigraphCruscalPrimBoruvka();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: остовное дерево, крускал
	const U_PTR(SpanningTree)& GetCruscalSpanTree()const;

	// получение: остовное дерево, прим
	const U_PTR(SpanningTree)& GetPrimSpanTree()const;

	// получение: остовное дерево, борувка
	const U_PTR(SpanningTree)& GetBoruvkaSpanTree()const;

};


#endif // !PRESETGRAPHMANT4_h
