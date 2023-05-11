#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Graph.h"

namespace ALGO
{
	// создание соотнесенного графа
	inline Graph CorrelatedGraph(
		const S_PTR(Graph)& _graph	// обычный граф
	)
	{
		// получение матрицы смежности обычного графа
		VertexMatrix corr_matr = _graph->adjacency_matrix();

		// получение соотнесенного графа
		for (int i = 0; i < corr_matr.size(); i++)
		{
			for (int j = 0; j < corr_matr.size(); j++)
			{
				// отображаем элементы матрицы относительно главной диагонали
				if (corr_matr[i][j])
					corr_matr[j][i] = 1;
			}
		}

		// создание и возврат соотнесенного графа
		return Graph(corr_matr);
	}

	// BFS поиск в ширину
	inline void BFS(
		const S_PTR(Graph)& _graph,				// граф
		const U_PTR(VertexArr)& _marked_vert,	// массив маркированный вершин
		const int& _start_vert,					// начальная вершина 
		const int& _numb_of_connetivity_comp	// номер компоненты связности
	)
	{
		INFO("BFS");

		// очередь текущих вершин
		VertexQueue vert_q;
		// добавление начальной вершины в очередь
		vert_q.push(_start_vert);
		// приписываем начальной вершине номер компоненты связности,
		// в котором она находится (маркируем ее)
		(*_marked_vert)[_start_vert] = _numb_of_connetivity_comp;

		// текущая вершина
		Vertex v;

		// пока очередь не пустая
		// обрабатываем соседние вершины
		while (!vert_q.empty())
		{
			// получаем текущую вершину
			v = vert_q.front();
			vert_q.pop();

			// проходимся по всем смежным вершинам
			for (const Vertex& ver : _graph->adjacency_list(v))
			{
				// если вершина не маркированная
				// добавляем ее в очередь и маркируем
				if (!(*_marked_vert)[ver])
				{
					vert_q.push(ver);
					(*_marked_vert)[ver] = _numb_of_connetivity_comp;
				}
			}
		}
	}

	// DFS поиск в глубину
	inline void DFS(
		const S_PTR(Graph)& _graph,				// граф
		const U_PTR(VertexArr)& _marked_vert,	// массив маркированный вершин
		const int& _start_vert,					// начальная вершина 
		const int& _numb_of_connetivity_comp,	// номер компоненты связности
		const S_PTR(VertexList)& _order = NULL	// список вершин для топологической сортировки
	)
	{
		INFO("DFS");

		std::stack<int> stk;
		stk.push(_start_vert);
		(*_marked_vert)[_start_vert] = _numb_of_connetivity_comp;

		while (!stk.empty())
		{
			// VertexList lst = _graph->adjacency_list(stk.top());
			// stk.pop();

			int vert = stk.top();
			stk.pop();
			VertexList lst = _graph->adjacency_list(vert);

			// цикл по всем смежным непосещенным вершинам
			auto it = lst.begin();
			for (; it != lst.end(); it++)
			{
				if (!(*_marked_vert)[*it])
				{
					stk.push(vert);
					(*_marked_vert)[*it] = _numb_of_connetivity_comp;
					stk.push(*it);
					break;
				}
			}

			// если нужно составлять очередь _order 
			if (_order)
			{
				_order->push_back(vert);
			}
		}
	}

	// TopologicalSort топологическая сортировка
	// получение списка вершин в порядке уменьшения времени выхода
	inline VertexList TopologicalSort(
		const S_PTR(Graph)& _graph	// граф
	)
	{
		INFO("Топологическая сортировка");

		// массив пройденных вершин
		U_PTR(VertexArr) used_vert = std::make_unique<VertexArr>(_graph->adjacency_matrix().size());

		// список вершин, заполненный в порядке увеличения времени выхода
		S_PTR(VertexList) order = std::make_shared<VertexList>();

		// цикл по всем непосещенным вершинам графа
		for (int i = 0; i < used_vert->size(); i++)
		{
			if(!(*used_vert)[i])
			{
				DFS(_graph, used_vert, i, 1, order);
			}
		}

		// разворот очереди
		std::reverse(order->begin(), order->end());

		return *order;
	}

	// DFS для поиска мостов
	// РЕКУРСИВНЫЙ
	inline void BridgeDFS(
		const S_PTR(Graph)& _graph,				// граф
		const U_PTR(VisitedVert)& _marked_vert,	// массив маркированный вершин
		const int& _start_vert,					// начальная вершина 
		const int& _cur_time,					// время начала алгоритма
		const U_PTR(VertexArr)& _tin,			// массив времени входа вершины
		const U_PTR(VertexArr)& _tout,			// массив времени выхода из вершины
		const U_PTR(EdgeList)& _bridges,		// список мостов
		const int& _parent = -1					// вершина-предок
	)
	{
		INFO("BridgeDFS");

		// помечаем текущую вершину
		(*_marked_vert)[_start_vert] = true;

		// устанавливаем врем входа и выхода (позже изменится)
		(*_tin)[_start_vert] = (*_tout)[_start_vert] = _cur_time;

		// получаем список соседних вершин
		VertexList lst = _graph->adjacency_list(_start_vert);

		// проходимся по всем смежным вершинам
		auto to = lst.begin();
		for (; to != lst.end(); to++)
		{
			// проход по ребру в обратную сторону
			if (*to == _parent)
				continue;

			// обратное ребро
			if ((*_marked_vert)[*to])
			{
				(*_tout)[_start_vert] = std::min((*_tout)[_start_vert], (*_tin)[*to]);
			}
			
			// прямое ребро дерева поиска
			else
			{
				// запускаем BridgeDFS для непройденной вершины
				BridgeDFS(_graph, _marked_vert, *to, _cur_time + 1, _tin, _tout, _bridges, _start_vert);

				// время выхода из начальной вершины
				(*_tout)[_start_vert] = std::min((*_tout)[_start_vert], (*_tout)[*to]);

				// добавляем ребро в список мостов
				// если tout[to] > tin[start_vert]
				if((*_tout)[*to] > (*_tin)[_start_vert])
				{
					_bridges->push_back({ _start_vert, *to });
				}
			}
		}
	}

	// DFS для поиска шарниров
	// РЕКУРСИВНЫЙ
	inline void PivotDFS(
		const S_PTR(Graph)& _graph,				// граф
		const U_PTR(VisitedVert)& _marked_vert,	// массив маркированный вершин
		const int& _start_vert,					// начальная вершина 
		const int& _cur_time,					// время начала алгоритма
		const U_PTR(VertexArr)& _tin,			// массив времени входа вершины
		const U_PTR(VertexArr)& _tout,			// массив времени выхода из вершины
		const U_PTR(PivotArr)& _pivot,			// список шарниров
		const int& _parent = -1					// вершина-предок
	)
	{
		INFO("PivotDFS");

		// помечаем текущую вершину
		(*_marked_vert)[_start_vert] = true;

		// устанавливаем врем входа и выхода (позже изменится)
		(*_tin)[_start_vert] = (*_tout)[_start_vert] = _cur_time;

		// если вершина-предок - корень,
		// тогда нужно посчитать число ее детей в дереве поиска
		int children = 0;

		// получаем список соседних вершин
		VertexList lst = _graph->adjacency_list(_start_vert);

		// проходимся по всем смежным вершинам
		auto to = lst.begin();
		for (; to != lst.end(); to++)
		{
			// проход по ребру в обратную сторону
			if (*to == _parent)
				continue;

			// обратное ребро
			if ((*_marked_vert)[*to])
			{
				(*_tout)[_start_vert] = std::min((*_tout)[_start_vert], (*_tin)[*to]);
			}

			// прямое ребро дерева поиска
			else
			{
				// запускаем BridgeDFS для непройденной вершины
				PivotDFS(_graph, _marked_vert, *to, _cur_time + 1, _tin, _tout, _pivot, _start_vert);

				// время выхода из начальной вершины
				(*_tout)[_start_vert] = std::min((*_tout)[_start_vert], (*_tout)[*to]);

				// добавляем вершину в список шарниров
				// если tout[to] >= tin[start_vert]
				if ((*_tout)[*to] >= (*_tin)[_start_vert] && _parent != -1)
				{
					(*_pivot)[_start_vert] = true;
				}

				children++;
			}
		}
		// если вершина-предок - корень
		if(_parent == -1 && children > 1)
			(*_pivot)[_start_vert] = true;

	}

}


#endif // !ALGORITHMS_HPP
