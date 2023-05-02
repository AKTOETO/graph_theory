#pragma once
#include "GraphManagerT1.h"
#include "../BaseScriptPrintManager.hpp"

class ScriptPrintManagerT1 : public BaseScriptPrintManager<ScriptPrintManagerT1, GraphManagerT1>
{
public:
	ScriptPrintManagerT1(std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script);
	virtual ~ScriptPrintManagerT1() override;

	//===================================//
	// МЕТОДЫ ПЕЧАТИ ХАРАКТЕРИСТИК ГРАФА //
	//===================================//

	// печать матрицы кратчайших расстояний
	void PrintShortestDistMatrix() const;

	// печать списка эксцентриситетов
	void PrintEccentricity() const;

	// печать центральных вершин
	void PrintCentralVertices() const;

	// печать периферийных вершин
	void PrintPeripheralVertices() const;

	// печать радиуса
	void PrintRadius() const;

	// печать диаметра
	void PrintDiameter() const;

	// печать степени входа вершины
	void PrintVertexDegreesIn() const;

	// печать степени выхода вершины
	void PrintVertexDegreesOut() const;

	// печать степени входа и выхода вершины
	void PrintVertexDegreesInOut() const;
};

