#include "pch.h"
#include "ScriptPrintManager.h"

ScriptPrintManager::ScriptPrintManager(
	std::string _filepath, INPUT_FILE_TYPE _in_f_type, Script _script
)
	: m_graph_manager(std::make_unique<GraphManager>(_filepath, _in_f_type)),
	m_script(std::make_unique<Script>(_script))
{
	m_specs =
	{
		{SPEC::SHORTEST_DIST_MATR,	&ScriptPrintManager::PrintShortestDistMatrix},
		{SPEC::ECCENTR,				&ScriptPrintManager::PrintEccentricity},
		{SPEC::CENTRAL_VERT,		&ScriptPrintManager::PrintCentralVertices},
		{SPEC::PERIPHERAL_VERT,		&ScriptPrintManager::PrintPeripheralVertices},
		{SPEC::RADIUS,				&ScriptPrintManager::PrintRadius},
		{SPEC::DIAMETER,			&ScriptPrintManager::PrintDiameter},
		{SPEC::DEGREES_IN,			&ScriptPrintManager::PrintVertexDegreesIn},
		{SPEC::DEGREES_OUT,			&ScriptPrintManager::PrintVertexDegreesOut},
		{SPEC::DEGREES_IN_OUT,		&ScriptPrintManager::PrintVertexDegreesInOut},
	};
}

ScriptPrintManager::~ScriptPrintManager()
{
	m_graph_manager.reset();
	m_script.reset();
}

void ScriptPrintManager::Run()
{
	std::for_each(m_script->begin(), m_script->end(), [&](const SPEC& spec)
		{
			m_graph_manager->CalculateSpecifier(spec);
		}
	);

	// TODO надо еще выводить величины
	// для вывода спрашивать у граф менеджера: 
	// расчитана ли эта велечина?
	// для всего сценария вызываем соответствующие функции печати
	std::for_each(m_script->begin(), m_script->end(), [&](const SPEC& el)
		{
			(this->*m_specs[el])();
		}
	);

}

#define IF_CALC(_spec) if((*m_graph_manager->GetStatesOfSpecs())[int(_spec)])

void ScriptPrintManager::PrintShortestDistMatrix() const
{
	// если была расчитана матрица кратчайших расстояний
	IF_CALC(SPEC::SHORTEST_DIST_MATR)
	{
		INFO("печать матрицы кратчайших расстояний");

		std::cout << "Distancies:\n";
		auto mat = *m_graph_manager->GetShortestDistMatr();
		int print_width = CountDigitInMatrix(mat);
		for (auto& el : mat)
		{
			std::cout << "[";
			PrintVector(el, " ", print_width);
			std::cout << "]\n";
		}
	}
}

void ScriptPrintManager::PrintEccentricity() const
{
	// если были расчитаны эксцентриситеты
	IF_CALC(SPEC::ECCENTR)
	{
		INFO("Печать массива эксцентриситетов");
		std::cout << "Eccentricity: [";
		PrintVector(*m_graph_manager->GetEccentricity(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManager::PrintCentralVertices() const
{
	IF_CALC(SPEC::CENTRAL_VERT)
	{
		INFO("печать центральных вершин");
		std::cout << "Z = [";
		PrintVector(*m_graph_manager->GetCentralVertices(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManager::PrintPeripheralVertices() const
{
	IF_CALC(SPEC::PERIPHERAL_VERT)
	{
		INFO("печать периферийных вершин");
		std::cout << "P = [";
		PrintVector(*m_graph_manager->GetPeripheralVertices(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManager::PrintRadius() const
{
	IF_CALC(SPEC::RADIUS)
	{
		INFO("печать радиуса");
		std::cout << "R = " << *m_graph_manager->GetRadius() << std::endl;
	}
}

void ScriptPrintManager::PrintDiameter() const
{
	IF_CALC(SPEC::DIAMETER)
	{
		INFO("печать диаметра");
		std::cout << "D = " << *m_graph_manager->GetDiameter() << std::endl;
	}
}

void ScriptPrintManager::PrintVertexDegreesIn() const
{
	// если были расчитаны степени входа
	IF_CALC(SPEC::DEGREES_IN)
	{
		INFO("печать степени входа");
		std::cout << "deg+ = [";
		PrintVector(*m_graph_manager->GetVertexDegreesIn(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManager::PrintVertexDegreesOut() const
{
	// если были расчитаны степени выхода
	IF_CALC(SPEC::DEGREES_OUT)
	{
		INFO("печать степени выхода");
		std::cout << "deg- = [";
		PrintVector(*m_graph_manager->GetVertexDegreesOut(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManager::PrintVertexDegreesInOut() const
{
	// если были расчитаны степени входа и выхода
	IF_CALC(SPEC::DEGREES_IN_OUT)
	{
		INFO("печать степени входа и выхода");
		std::cout << "deg = [";
		PrintVector(*m_graph_manager->GetVertexDegreesInOut(), ", ");
		std::cout << "]\n";
	}
}

void ScriptPrintManager::PrintIsConnected() const
{
	IF_CALC(SPEC::IS_CONNECTED)
	{
		INFO("печать: граф связен");
		std::cout << "Graph is connected.\n";
	}
}

void ScriptPrintManager::PrintIsNotConnected() const
{
}

void ScriptPrintManager::PrintConnectedComponents() const
{
}

void ScriptPrintManager::PrintIsDigraphConnected() const
{

}

void ScriptPrintManager::PrintIsDigraphNotConnected() const
{
}

void ScriptPrintManager::PrintIsDigraphWeaklyConnected() const
{
}

void ScriptPrintManager::PrintIsDigraphStronglyConnected() const
{
	IF_CALC(SPEC::IS_STRONGLY_CONNECTED)
	{
		INFO("печать: граф сильно связен");
		std::cout << "Digraph is strongly connected.\n";
	}
}

void ScriptPrintManager::PrintStronglyConnectedComponents() const
{
}
