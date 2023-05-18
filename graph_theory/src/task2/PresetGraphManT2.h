#ifndef PRESETGRAPHMANT2_h
#define PRESETGRAPHMANT2_h

#include "../base/BasePresetGraphMan.hpp"

// набор функций для решения второй задачи
class PresetGraphManT2 : virtual public BaseGraphPresetManager
{
protected:
	// маркированные вершины графа (орграфа)
	// индекс в массиве    = номер вершины
	// значение по индексу = номер компоненты связности (комп. слабой связности орграфа)
	U_PTR(VertexArr) m_marked_vertices;
	
	// маркированные вершины ориентированного графа (комп. сильной связности)
	U_PTR(VertexArr) m_digraph_marked_vertices;

	// количество компонент связности (комп. слабой связности)
	int m_numb_of_conn_compon;

	// количество компонент сильной связности
	int m_numb_of_strng_con_comp;

	// связен ли граф
	bool m_is_connected;

	// сильно связен ли граф
	bool m_is_strongly_connected;

public:

	// конструктор и деструктор
	PresetGraphManT2(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT2() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: связен ли граф
	bool CalculateIsConnected();

	// расчет: не связен ли граф
	bool CalculateIsNotConnected();

	// расчет: компоненты связности
	bool CalculateConnectedComponents();

	// расчет: связен ли диграф
	bool CalculateIsDigraphConnected();

	// расчет: не связен ли диграф
	bool CalculateIsDigraphNotConnected();

	// расчет: слабо ли свзяен диграф
	bool CalculateIsDigraphWeaklyConnected();

	// расчет: сильно ли свзяен диграф
	bool CalculateIsDigraphStronglyConnected();

	// расчет: компоненты сильной связности
	bool CalculateDStronglyConnectedComponents();

	// расчет: компоненты связности в ориентированном графе
	bool CalculateDWeaklyConnectedComponents();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: количество компонент слабой связности
	const int& GetNumberOfConnectedComponents() const;

	// получение: компоненты слабой связности
	const U_PTR(VertexArr)& GetConnectedComponents() const;

	// получение: связен ли граф
	const bool& GetIsGraphConnected() const;

	// получение: компоненты сильной связности
	const U_PTR(VertexArr)& GetStronglyConnectedComponents() const;

	// получение: количество компонент сильной связности
	const int& GetNumberOfStronglyConnectedComponents() const;

	// получение: сильно связен ли орграф
	const bool& GetIsDigraphStronglyConnected();

};

#endif // !PRESETGRAPHMANT2_h
