#ifndef PRESETGRAPHMANT3_h
#define PRESETGRAPHMANT3_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT3 :
	virtual public BaseGraphPresetManager
{
protected:
	// маркированные вершины графа (орграфа)
	U_PTR(VisitedVert) m_marked_vertices;

	// массив времени входа
	U_PTR(TimeArr) m_tin;

	// массив времени выхода
	U_PTR(TimeArr) m_tout;

	// список мостов
	U_PTR(EdgeList) m_bridges;

	// массив шарниров
	U_PTR(PivotArr) m_pivots;

public:
	// конструктор и деструктор
	PresetGraphManT3(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT3() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: мосты в графе
	bool CalculateBridges();

	// расчет: шарниры в графе
	bool CalculatePivots();

	// расчет: мосты в диграфе
	bool CalculateDigraphBridges();

	// расчет: шарниры в диграфе
	bool CalculateDigraphPivots();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: мосты в графе/ографе
	const U_PTR(EdgeList)& GetBridges() const;

	// получение: шарниры в графе/ографе
	const U_PTR(PivotArr)& GetPivots() const;

};

#endif // !PRESETGRAPHMANT3_h
