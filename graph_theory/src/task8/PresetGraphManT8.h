#ifndef PRESETGRAPHMANT8_h
#define PRESETGRAPHMANT8_h

#include "../base/BasePresetGraphMan.hpp"

enum class Heuristics
{
	MANHATTAN,
	CHEBYSHEV,
	EUCLID,
	DIJKSTRA
};

class PresetGraphManT8 :
	virtual public BaseGraphPresetManager
{
protected:

	// количество эвристик 
	int numb_of_heur;

	// кратчайшие расстояния для 4ех эвристик
	std::vector<S_PTR(CellVector)> m_dist;

	// Длина кратчайшего расстояния для всех эвристик
	U_PTR(WeightVector) m_dist_length;

	// пройденные клетки для всех эвристик
	std::vector<S_PTR(VisitedCell)> m_used_cell;

	// массив эвристик
	std::vector<HeuristicFunc> m_heur_func;

	// карта
	U_PTR(Map) m_map;

public:
	// конструктор и деструктор
	PresetGraphManT8(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT8() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: Кратчайшее расстояние A*
	bool CalculateAStarShortestPath();

	// расчет: Длина кратчайшео расстояния
	bool CalculateAStarShortestPathLength();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: Кратчайшее расстояние A*
	const std::vector<S_PTR(CellVector)>& GetAStarShortestPath() const;

	// получение: Длина кратчайшео расстояния
	const WeightVector& GetAStarShortestPathLength() const;

	// получение: Пройденные клетки
	const std::vector<double> GetAStarPercentUsedCells() const;
};

#endif // !PRESETGRAPHMANT6_h
