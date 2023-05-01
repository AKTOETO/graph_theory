#pragma once
#include "Graph.h"

/// <summary>
/// Класс для управления графом
/// </summary>
class GraphManager
{
private:

	// Сам граф
	U_PTR(Graph) m_graph;

	// просчитана ли характеристика
	// 1 - просчитана
	// 0 - не просчитана
	U_PTR(std::vector<bool>) m_state_of_spec;

	// матрица кратчайших расстояний
	U_PTR(VertexMatrix) m_shortest_distance_matr;

	// эксцентриситет вершин графа
	U_PTR(VertexArr) m_eccentricity;

	// множество центральных вершин
	U_PTR(VertexArr) m_central_vertices;

	// множество периферийных вершин
	U_PTR(VertexArr) m_peripheral_vertices;

	// радиус графа
	U_PTR(int) m_radius;

	// диаметр графа
	U_PTR(int) m_diameter;

	// массив степеней входа в вершины
	U_PTR(VertexArr) m_degrees_in;

	// массив степеней выхода в вершины
	U_PTR(VertexArr) m_degrees_out;

	// массив степеней входа и выхода из вершины
	U_PTR(VertexArr) m_degrees_in_out;

	// установить состояние характеристики
	// 1 - просчитана
	// 0 - не просчитана
	void SetStateOfSpec(SPEC, bool);

public:

	// конструктор с путем до файла и типом файла
	GraphManager(std::string _filepath, INPUT_FILE_TYPE);
	~GraphManager();

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	/// <summary>
	/// Расчет определенной характеристики
	/// </summary>
	/// <param name="_spec"> - характеристика, которую надо расчитать</param>
	/// <returns></returns>
	void CalculateSpecifier(SPEC _spec);

	/// <summary>
	/// Расчет степени входа вершины
	/// </summary>
	/// <returns>сама степень вершины</returns>
	bool CalculateVertexDegreesIn();

	/// <summary>
	/// Расчет степени выхода вершины
	/// </summary>
	/// <returns>сама степень вершины</returns>
	bool CalculateVertexDegreesOut();

	/// <summary>
	/// Расчет степени входа и выхода вершины
	/// </summary>
	/// <returns>сама степень вершины</returns>
	bool CalculateVertexDegreesInOut();

	/// <summary>
	/// Расчет матрицы кратчайших расстояний
	/// </summary>
	/// <returns>матрица кратчайших расстояний</returns>
	bool CalculateShortestDistMatr();

	/// <summary>
	/// Расчет эксцентриcитета графа
	/// </summary>
	/// <returns>массив с эксцентриситетом для каждой вершины</returns>
	bool CalculateEccentricity();

	/// <summary>
	/// Расчет диаметра графа
	/// </summary>
	/// <returns>диаметр графа</returns>
	bool CalculateDiameter();

	/// <summary>
	/// Расчет радиуса гарфа
	/// </summary>
	/// <returns>радиус гарфа</returns>
	bool CalculateRadius();

	/// <summary>
	/// Расчет центральных вершин
	/// </summary>
	/// <returns>центральные вершины</returns>
	bool CalculateCentralVertices();

	/// <summary>
	/// Расчет периферийных вершин
	/// </summary>
	/// <returns>периферийные вершины</returns>
	bool CalculatePeripheralVertices();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	/// <summary>
	/// Получение степени вершины входа
	/// </summary>
	/// <returns>сама степень вершины</returns>
	const U_PTR(VertexArr)& GetVertexDegreesIn() const;

	/// <summary>
	/// Получение степени вершины выхода
	/// </summary>
	/// <returns>сама степень вершины</returns>
	const U_PTR(VertexArr)& GetVertexDegreesOut() const;

	/// <summary>
	/// Получение степени вершины входа и выхода
	/// </summary>
	/// <returns>сама степень вершины</returns>
	const U_PTR(VertexArr)& GetVertexDegreesInOut() const;

	/// <summary>
	/// Получение матрицы кратчайших расстояний
	/// </summary>
	/// <returns>матрица кратчайших расстояний</returns>
	const U_PTR(VertexMatrix)& GetShortestDistMatr() const;

	/// <summary>
	/// получение эксцентриcитета графа
	/// </summary>
	/// <returns>массив с эксцентриситетом для каждой вершины</returns>
	const U_PTR(VertexArr)& GetEccentricity() const;

	/// <summary>
	/// Получение диаметра графа
	/// </summary>
	/// <returns>диаметр графа</returns>
	const U_PTR(int)& GetDiameter() const;

	/// <summary>
	/// Получение радиуса гарфа
	/// </summary>
	/// <returns>радиус гарфа</returns>
	const U_PTR(int)& GetRadius() const;

	/// <summary>
	/// Получение центральных вершин
	/// </summary>
	/// <returns>центральные вершины</returns>
	const U_PTR(VertexArr)& GetCentralVertices() const;

	/// <summary>
	/// Получение периферийных вершин
	/// </summary>
	/// <returns>периферийные вершины</returns>
	const U_PTR(VertexArr)& GetPeripheralVertices() const;


	/// <summary>
	/// получение состояния всех характеристик
	/// </summary>
	/// <returns>указатель на вектор</returns>
	const U_PTR(std::vector<bool>)& GetStatesOfSpecs() const;
};

