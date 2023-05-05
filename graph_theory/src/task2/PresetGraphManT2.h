#pragma once
#include "../base/BasePresetGraphMan.hpp"

/// <summary>
/// Класс для управления графом
/// </summary>
class PresetGraphManT2 : virtual public BaseGraphManager
{
protected:
	// маркированные веришны
	// индекс в массиве    = номер вершины
	// значение по индексу = номер компоненты связности
	U_PTR(VertexArr) m_marked_vertices;
	
	// количество компонент связности
	int m_numb_of_conn_compon;


public:

	// конструктор с путем до файла и типом файла
	PresetGraphManT2(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states);
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
	bool CalculateStronglyConnectedComponents();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: количество компонент связности
	const int& GetNumbOfConnComp() const;

	// получение: компоненты связности

	// получение: компоненты сильной связности

	// получение: количество компонент сильной связности

};

