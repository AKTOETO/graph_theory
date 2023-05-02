#pragma once
#include "../BaseGraphManager.hpp"

/// <summary>
/// Класс для управления графом
/// </summary>
class GraphManagerT2 : public BaseGraphManager<GraphManagerT2>
{
protected:
	// поля класса

public:

	// конструктор с путем до файла и типом файла
	GraphManagerT2(std::string _filepath, INPUT_FILE_TYPE);
	~GraphManagerT2() override;

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

	// получение: компоненты связности

	// получение: компоненты сильной связности

	// получение: количество компонент сильной связности

};

