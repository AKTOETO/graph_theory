#ifndef PRESETGRAPHMANT8_h
#define PRESETGRAPHMANT8_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT8 :
    virtual public BaseGraphPresetManager
{
protected:

	// Кратчайшее расстояние
	U_PTR(CellVector) m_dist;

	// Длина кратчайшего расстояния
	U_PTR(int) m_dist_length;

	// пройденные клетки
	U_PTR(VisitedCell) m_used_cell;

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
	const U_PTR(CellVector)& GetAStarShortestPath() const;

	// получение: Длина кратчайшео расстояния
	const U_PTR(int)& GetAStarShortestPathLength() const;
};

#endif // !PRESETGRAPHMANT6_h
