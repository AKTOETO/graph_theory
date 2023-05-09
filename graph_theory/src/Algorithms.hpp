#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Graph.h"

namespace ALGO
{
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

}


#endif // !ALGORITHMS_HPP
