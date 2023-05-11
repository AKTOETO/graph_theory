#pragma once
#include "../base/BasePresetScriptMan.hpp"

class PresetScriptManT1 : virtual public BaseScriptPreset
{
public:

	PresetScriptManT1(const S_PTR(GraphManager)& _graph_man);
	virtual ~PresetScriptManT1() override;

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

