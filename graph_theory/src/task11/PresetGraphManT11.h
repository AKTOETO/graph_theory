#ifndef PRESETGRAPHMANT11_h
#define PRESETGRAPHMANT11_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT11 :
	virtual public BaseGraphPresetManager
{
protected:

	// матрица остаточной пропускной способности
	S_PTR(VertexMatrix) m_bandwidth;

	// маркированные вершины
	U_PTR(VertexArr) m_used;

	// двудольный ли граф
	bool m_is_bipartite;

	// список паросочетаний
	EdgeList m_lst;

	// количество ребер
	int m_edges;

public:
	// конструктор и деструктор
	PresetGraphManT11(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT11() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: Двудольный ли граф
	bool CalculateIsBipartite();

	// расчет: НЕ Двудольный ли граф
	bool CalculateIsNotBipartite();

	// расчет: максимальное паросочетание
	bool CalculateMaxMatching();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: двудольный ли граф
	bool GetIsBipartite() const;

	// получение: Паросочетание
	const EdgeList& GetMatching() const;

	// получение: количество ребер
	const int& GetEdgeNumber() const;
};

#endif // !PRESETGRAPHMANT10_h
