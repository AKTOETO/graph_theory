#ifndef PRESETGRAPHMANT5_h
#define PRESETGRAPHMANT5_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT5 :
    virtual public BaseGraphPresetManager
{
protected:
	// вектор полученный из алгоритма Дейкстры
	// для восстановления пути
	//U_PTR(VertexArr) m_parent;
	// список ребер кратчайшего расстояния 
	EdgeList m_short_dist_edge_list;

	// кратчайшее расстояние
	Weight m_dist_manh;

public:
	// конструктор и деструктор
	PresetGraphManT5(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT5() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: кратчайшего расстояния, Дейкстра
	bool CalculateShortPathDijkstra();

	// расчет: есть ли кратчайший путь
	bool CalculateThereIsShortestPath();

	// расчет: нет ли кратчайшего пути
	bool CalculateThereIsNotShortestPath();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: кратчайшее расстояние
	const Weight& GetShortestDistToVert() const;

	// получение: список ребер кратчайшего пути
	const EdgeList& GetShortestDistEdgeList() const;

};

#endif // !PRESETGRAPHMANT5_h
