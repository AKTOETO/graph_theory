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
		INFO("получение соотнесенного графа");

		// получение матрицы смежности обычного графа
		VertexMatrix corr_matr = _graph->adjacency_matrix();

		// получение соотнесенного графа
		for (int i = 0; i < corr_matr.size(); i++)
		{
			for (int j = 0; j < corr_matr.size(); j++)
			{
				// отображаем элементы матрицы относительно главной диагонали
				if (corr_matr[i][j])
					corr_matr[j][i] = corr_matr[i][j];
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
			if (!(*used_vert)[i])
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
				if ((*_tout)[*to] > (*_tin)[_start_vert])
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
		if (_parent == -1 && children > 1)
			(*_pivot)[_start_vert] = true;

	}

	// Алгоритм Крускала O(E log V) 
	// поиск мин. остовного дерева
	inline SpanningTree Kruskal(
		const S_PTR(Graph)& _graph	// граф
	)
	{
		INFO("Kruskal");

		// выходное остовное дерево
		SpanningTree res;

		// сортировка ребер по весу
		EdgeList edges = _graph->list_of_edges();
		edges.sort([](const Edge& _ed, const Edge& _ed2)
			{
				return _ed.m_weight < _ed2.m_weight;
			}
		);

		// создане системы неперсекающихся множеств,
		// для хранения компонент
		DSU comp(_graph->adjacency_matrix().size());

		// проходимся по всем ребрам
		for (Edge& _ed : edges)
		{
			// если ребро соединяет разные компоненты связности
			// добавляем его в остовное дерево
			if (comp.FindSet(_ed.m_from) != comp.FindSet(_ed.m_to))
			{
				// объединяем эти компоненты
				// увеичичваем вес остовного дерева
				// запоминаем это ребро
				comp.UnionSet(_ed.m_from, _ed.m_to);
				res.m_weight += _ed.m_weight;
				res.m_edge_list.push_back(_ed);
			}
		}

		return res;
	}

	// Алгоритм Прима O(E * logV)
	// поиск мин. остовного дерева
	inline SpanningTree Prim(
		const S_PTR(Graph)& _graph	// граф
	)
	{
		INFO("Prim");

		// выходное остовное дерево
		SpanningTree res;

		// очередь инцидентных вершине ребер
		std::priority_queue<Edge, EdgeArr, EdgeGreater> p_q;

		// вектор посещенных вершин
		VisitedVert used(_graph->adjacency_matrix().size());

		// вектор минимальных весов к вершинам,
		// индекс в векторе - номер вершины
		VertexArr weights(_graph->adjacency_matrix().size(), INF);

		// начинаем с первой вершины
		p_q.push({ 0,0,0 });
		weights[0] = 0;

		// пока очередь не пуста
		while (!p_q.empty())
		{
			// вынимаем из очереди ребро с минимальным весом
			Edge min_ed = p_q.top();
			p_q.pop();

			// если вершины еще нет в остовном дереве
			if (!used[min_ed.m_to])
			{
				// помечаем вершину и увеличиваем вес дерева
				used[min_ed.m_to] = true;
				res.m_weight += min_ed.m_weight;

				// добавляем ребро в дерево
				res.m_edge_list.push_back(min_ed);

				// добавляем в очередь инцидентные ребра вершине min_ed.m_to
				EdgeList ed_lst = _graph->list_of_edges(min_ed.m_to);
				for (auto it = begin(ed_lst); it != end(ed_lst); it++)
				{
					// если вершина, в которую направлено ребро,
					// еще не была посещена - добавляем ребро
					if (!used[it->m_to] && (weights[it->m_to] > it->m_weight))
					{
						weights[it->m_to] = it->m_weight;
						p_q.push(*it);
					}
				}
			}
		}
		// удаление первого (нулевого) ребра 
		res.m_edge_list.erase(res.m_edge_list.begin());

		return res;
	}

	// Алгоритм Борувки O(E log V)
	// поиск мин. остовного дерева
	inline SpanningTree Boruvka(
		const S_PTR(Graph)& _graph	// граф
	)
	{
		INFO("Boruvka");

		// изначальное количество деревьев
		// (по алгоритму, все вершины - отдельные деревья)
		size_t num_of_trees = _graph->adjacency_matrix().size();

		// выходная структура с остовным деревом
		SpanningTree res;

		// массив для хранения кротчайших ребер
		// из подмножества.
		EdgeArr cheapest(num_of_trees, { -1,-1,-1 });

		// создане системы неперсекающихся множеств,
		// для хранения компонент
		DSU comp(num_of_trees);

		//// каждому подмножеству назначаем родителем самого себя
		//for (int i = 0; i < num_of_trees; i++)
		//{
		//	comp.MakeSet(i);
		//}

		// список ребер в графе
		EdgeList elst = _graph->list_of_edges();
		elst.sort([](const Edge& _ed, const Edge& _ed2)
			{
				return _ed.m_weight < _ed2.m_weight;
			}
		);

		// объединям компоненты, пока их больше одной
		while (num_of_trees > 1)
		{
			// проходим по всем ребрам
			// и находим ребро с минимальным весом
			// для каждой компоненты
			for (auto it = elst.begin(); it != elst.end(); it++)
			{
				// выясняем к каким множествам относятся вершины,
				// которые находятся на концах текущего ребра
				int set1 = comp.FindSet(it->m_from);
				int set2 = comp.FindSet(it->m_to);

				// если обе вершины находятся в разных компонентах,
				// то проверяем, если текущее ребро короче того,
				// что находится в массиве кратчайших ребер cheapest
				// то мы обновляем кратчайшее ребро для текущих множеств
				if (set1 != set2)
				{
					// для первого множества
					if (
						cheapest[set1].m_weight == -1 ||
						cheapest[set1].m_weight > it->m_weight
						)
					{
						cheapest[set1] = *it;
					}

					// для второго мноества
					if (
						cheapest[set2].m_weight == -1 ||
						cheapest[set2].m_weight > it->m_weight
						)
					{
						cheapest[set2] = *it;
					}
				}

				// учтем только что найденные кратчайшие ребра и 
				// добавим их в минимальноей остовное дерево
				for (Edge& el : cheapest)
				{
					// если кратчайшее ребро для текущего множества
					// (компоненты связности) существует
					if (el.m_weight != -1)
					{
						// выясняем к каким множествам относятся вершины,
						// которые находятся на концах текущего ребра
						set1 = comp.FindSet(el.m_from);
						set2 = comp.FindSet(el.m_to);

						// если обе вершины находятся в разных компонентах,
						// объединяем компоненты, добавляем ребро в МОД
						// увеличиваем размер МОД (минимального остовного дерева)
						// уменьшаем количество компонент
						if (set1 != set2)
						{
							res.m_weight += el.m_weight;
							res.m_edge_list.push_back(el);

							comp.UnionSet(set1, set2);
							num_of_trees--;
						}
					}
				}

				// сбрасываем массив с кратчайшими ребрами
				for (Edge& el : cheapest)
				{
					el.m_weight = -1;
				}
			}
		}

		return res;
	}
}


#endif // !ALGORITHMS_HPP
