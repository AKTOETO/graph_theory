#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Graph.h"
#include "Map.h"

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

	// конвертация вектора полученного из алгоритма Дейкстры
	// в список ребер
	inline EdgeList ConvDijksrtasVectToEdgeList(
		const S_PTR(Graph)& _graph,			// обычный граф
		const U_PTR(VertexArr)& _parent,	// вектор родителей из Дейкстры
		const Vertex& _start,				// начальная вершина цепи
		const Vertex& _end					// конечная вершина цепи
	)
	{
		// выходной список ребер
		EdgeList out;

		// проходимся по всем вершинам в массиве _parent
		for (Vertex curr_vert = _end; curr_vert != _start;)
		{

			out.push_back(
				{
					(*_parent)[curr_vert],		// откуда
					curr_vert,					// куда
					// вес
_graph->adjacency_matrix()[(*_parent)[curr_vert]][curr_vert]
				}
			);

			// переход к следующей вершине
			curr_vert = (*_parent)[curr_vert];
			if (curr_vert == -1) ERROR("Отрицательный предок");
		}

		// разворачиваем список ребер
		out.reverse();

		return out;
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
		for (auto to = lst.begin(); to != lst.end(); to++)
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

	// Алгоритма Дейкстры O(E logV)
	// поиск кратчайшего пути 
	inline int Dijkstra(
		const S_PTR(Graph)& _graph,	// граф
		const int& _start,			// начальная вершина
		const int& _end,			// конечная вершина
		U_PTR(VertexArr)& _dist,	// расстояния до вершин от начальной
		U_PTR(VertexArr)& _parent	// вектор восстановления пути
	)
	{
		// очередь обрабатываемых вершин
		std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

		// создаем массив расстояний до всех вершин 
		// и заполняем его бесконечностями
		_dist = std::make_unique<VertexArr>(_graph->adjacency_matrix().size(), INF);

		// создаем массив пути и заполняем его -1
		_parent = std::make_unique<VertexArr>(_graph->adjacency_matrix().size(), -1);

		// добавляем начальную вершину _start в очередь
		// и присваиваем расстояние до нее равное 0
		pq.push(std::make_pair(0, _start));
		(*_dist)[_start] = 0;

		// пока есть обрабатываемые вершины в очереди
		while (!pq.empty())
		{
			// получение индекса вершины с минимальным расстоянием
			int u = pq.top().second;
			pq.pop();

			// получение списка инцидентных ребер вершине u
			EdgeList edl = _graph->list_of_edges(u);

			// проходимся по всем смежным вершинам для вершины u,
			// чтобы добавить их в очередь обрабатываемых вершин
			// и пересчитать расстояние до них
			for (auto edge = begin(edl); edge != end(edl); edge++)
			{
				// если дистанция он вершины _start до edge->to
				// больше, чем дистанция от _start до u + edge->weight
				if ((*_dist)[edge->m_to] > ((*_dist)[u] + edge->m_weight))
				{
					// обновляем дистанцию
					(*_dist)[edge->m_to] = ((*_dist)[u] + edge->m_weight);

					// добавляем вершину в вектор восстановления пути
					(*_parent)[edge->m_to] = u;

					// добавляем вершину edge->to в очередь
					pq.push(std::make_pair((*_dist)[edge->m_to], edge->m_to));
				}
			}
		}

		// возврат расстояния от _start до _end
		return (*_dist)[_end];
	}

	// Алгоритм Дейкстры для отрицательных ребер
	// поиск кратчайшего пути O(E * logV)
	inline int NegativeDijkstra(
		const S_PTR(Graph)& _graph,	// граф
		const int& _start,			// начальная вершина
		const int& _end,			// конечная вершина
		U_PTR(VertexArr)& _dist,	// расстояния до вершин от начальной
		U_PTR(VertexArr)& _parent,	// вектор восстановления пути
		bool& _is_neg_cycle			// есть ли отрицательный цикл
	)
	{
		// очередь обрабатываемых вершин
		std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

		// количество вершин в графе
		size_t vsize = _graph->adjacency_matrix().size();

		// множество пройденных вершин
		StateVector passed(vsize, 0);

		// массив, хранящий количество раз обработки вершин
		// нужен для нахождения отрицательного цикла
		VertexArr number_of_passes(vsize, 0);

		// создаем массив расстояний до всех вершин 
		// и заполняем его бесконечностями
		_dist = std::make_unique<VertexArr>(vsize, INF);

		// создаем массив пути и заполняем его -1
		_parent = std::make_unique<VertexArr>(vsize, -1);

		// добавляем начальную вершину _start в очередь
		// и присваиваем расстояние до нее равное 0
		pq.push(std::make_pair(0, _start));
		(*_dist)[_start] = 0;

		// пока есть обрабатываемые вершины в очереди
		while (!pq.empty())
		{
			// получение индекса вершины с минимальным расстоянием
			int u = pq.top().second;
			int dst = pq.top().first;
			pq.pop();

			// увеличиваем количество раз обработки текущей вершины
			number_of_passes[u]++;

			// помечаем вершину, как пройденную
			passed[u] = 1;

			// если существует верщина с количеством раз обработки
			// равным или большим количеству вершин в графе, то 
			// был найден отрицательный цикл
			if (number_of_passes[u] >= vsize)
			{
				_is_neg_cycle = 1;
				return -1;
			}

			// пропускаем повтор
			if ((*_dist)[u] != dst)
			{
				continue;
			}

			// получение списка инцидентных ребер вершине u
			EdgeList edl = _graph->list_of_edges(u);

			// счетчик изменении
			// (найдено более короткое расстояние)
			int changes_counter = 0;

			// проходимся по всем смежным вершинам для вершины u,
			// чтобы добавить их в очередь обрабатываемых вершин
			// и пересчитать расстояние до них
			for (auto edge = begin(edl); edge != end(edl); edge++)
			{
				// если дистанция он вершины _start до edge->to
				// больше, чем дистанция от _start до u + edge->weight
				if ((*_dist)[edge->m_to] > ((*_dist)[u] + edge->m_weight))
				{
					// обновляем дистанцию
					(*_dist)[edge->m_to] = ((*_dist)[u] + edge->m_weight);

					// добавляем вершину в вектор восстановления пути
					(*_parent)[edge->m_to] = u;

					// добавляем вершину edge->to в очередь
					pq.push(std::make_pair((*_dist)[edge->m_to], edge->m_to));

					changes_counter++;
				}
				// если новое расстояние больше, то делаем неокрашенными обе вершины
				else if (passed[edge->m_to])
				{
					passed[edge->m_from] = 0;
					passed[edge->m_to] = 0;
				}
			}

			// окрашены ли все вершины
			bool all_colored = 1;
			for (int i = 0; i < vsize; i++)
			{
				if (!passed[i])
				{
					all_colored = 0;
					break;
				}
			}

			// если все вершины были пройдены и нет никакних изменений
			if (!changes_counter && all_colored)
				break;
		}

		// возврат расстояния от _start до _end
		return (*_dist)[_end];
	}

	// Алгоритм Беллмана Форда
	// поиск кратчайшего пути O(V * E)
	inline int BellmanFord(
		const S_PTR(Graph)& _graph,	// граф
		const int& _start,			// начальная вершина
		const int& _end,			// конечная вершина
		U_PTR(VertexArr)& _dist,	// расстояния до вершин от начальной
		bool& _is_neg_cycle			// есть ли отрицательный цикл
	)
	{
		// количество вершин в графе
		size_t vsize = _graph->adjacency_matrix().size();

		// создаем массив расстояний до всех вершин 
		// и заполняем его бесконечностями 
		// кроме начальной вершины
		_dist = std::make_unique<VertexArr>(vsize, INF);
		(*_dist)[_start] = 0;

		// получение списка ребер графа
		EdgeList edl = _graph->list_of_edges();

		// создание кратчайших путей от начальной вершины
		// до всех остальных
		// цикл vsize - 1 раз
		for (int i = 0; i < vsize - 1; i++)
		{
			// цикл по всем ребрам
			for (auto edge = begin(edl); edge != end(edl); edge++)
			{
				// если расстояние до вершины, из которй исходит ребро,
				// существует и расстояние до этой вершины через ребро короче
				if ((*_dist)[edge->m_from] != INF &&
					(*_dist)[edge->m_from] + edge->m_weight < (*_dist)[edge->m_to])
				{
					(*_dist)[edge->m_to] = (*_dist)[edge->m_from] + edge->m_weight;
				}
			}
		}

		// поиск отрицательных циклов
		// цикл по всем ребрам
		for (auto edge = begin(edl); edge != end(edl); edge++)
		{
			// если расстояние до вершины, из которй исходит ребро,
			// существует и расстояние до этой вершины через ребро короче
			if ((*_dist)[edge->m_from] != INF &&
				(*_dist)[edge->m_from] + edge->m_weight < (*_dist)[edge->m_to])
			{
				// граф содержит отрицательный цикл
				_is_neg_cycle = 1;
				return -1;
			}
		}

		return (*_dist)[_end];
	}

	// Алгоритм Левита
	// поиск кратчайшего пути O(n*n*m)
	inline int Levit(
		const S_PTR(Graph)& _graph,	// граф
		const int& _start,			// начальная вершина
		const int& _end,			// конечная вершина
		U_PTR(VertexArr)& _dist	// расстояния до вершин от начальной
	)
	{
		// количество вершин в графе
		size_t vsize = _graph->adjacency_matrix().size();

		// создаем массив расстояний до всех вершин 
		// и заполняем его бесконечностями 
		// кроме начальной вершины
		_dist = std::make_unique<VertexArr>(vsize, INF);
		(*_dist)[_start] = 0;

		std::set<Vertex> M0;	// вершины, расстояние до которых уже вычислено
		std::set<Vertex> M1;	// множество элементов в очереди
		std::queue<Vertex> M11;	// основнаяя очередь на обработку
		std::queue<Vertex> M12;	// срочная очередь
		std::set<Vertex> M2;	// вершины, расстояние до которых еще не вычислено

		// добавляем начальную вершину в очередь на обработку
		M11.push(_start);
		M1.insert(_start);

		// заполянем множество необработанных вершин
		for (int i = 0; i < vsize; i++)
			if (i != _start) M2.insert(i);

		// пока очереди М11 и М12 не пусты
		while (!M1.empty())
		{
			// вершина из М12 или из М11
			Vertex u;

			// если M12 не пусто
			if (!M12.empty())
				u = M12.front(), M12.pop();
			// иначе берем вршину из M11
			else
				u = M11.front(), M11.pop();

			// удаление элемента u из общего множества 
			M1.erase(u);

			// цикл по ребрам инцидентным вершине u
			EdgeList edl = _graph->list_of_edges(u);
			for (auto edge = begin(edl); edge != end(edl); edge++)
			{
				// конец ребра
				Vertex v = edge->m_to;

				// v принадлежит M2
				if (M2.find(v) != M2.end())
				{
					// переносим v в М11
					M11.push(v), M1.insert(v);
					M2.erase(v);

					// релаксация ребра
					(*_dist)[v] = std::min(
						(*_dist)[v],
						(*_dist)[u] + edge->m_weight
					);
				}
				// v принадлежит множеству М1
				else if (M1.find(v) != M1.end())
				{
					(*_dist)[v] = std::min(
						(*_dist)[v],
						(*_dist)[u] + edge->m_weight
					);
				}
				// v принадлежит M0 и dist[v]>dist[u]+weight[uv]
				else if (
					M0.find(v) != M0.end() &&
					(*_dist)[v] > (*_dist)[u] + edge->m_weight
					)
				{
					M12.push(v), M1.insert(v);
					M0.erase(v);
					(*_dist)[v] = (*_dist)[u] + edge->m_weight;
				}
			}
			M0.insert(u);
		}
		return (*_dist)[_end];
	}

	// Алгоритм Джонсона
	// поиск кратчайшего пути O(n*n*m)
	inline bool Jhonson(
		const S_PTR(Graph)& _graph,
		//U_PTR(PointerMatrix)& _dist	// расстояния от всех вершин до остальных
		U_PTR(VertexMatrix)& _dist	// расстояния от всех вершин до остальных
	)
	{
		EdgeList lst = _graph->list_of_edges();
		size_t sizem = _graph->adjacency_matrix().size();
		_dist = std::make_unique<VertexMatrix>(sizem, VertexArr(sizem, 0));

		// создание нового списка ребер
		U_PTR(EdgeList) lst2 = std::make_unique<EdgeList>(lst);

		// добавление новых ребер
		for (int i = 0; i < sizem; i++)
			lst2->push_back({ Vertex(sizem), i, NULLW });

		// создание нового графа
		S_PTR(Graph) gr = std::make_shared<Graph>(*lst2);

		// вектор весов
		U_PTR(VertexArr) h;

		// Поиск расстояний от новой вершины до остальных
		// есть ли отрицателдьный цикл
		bool neg_cycle = 0;

		// поиск расстояний от новой вершины до остальных
		BellmanFord(gr, static_cast<int>(sizem), 0, h, neg_cycle);

		// если есть отрицательный цикл, выходим
		if (neg_cycle) return 1;

		// удаление новых ребер
		lst2->remove_if([&](Edge& ed) {return ed.m_from == sizem; });

		// пересчет весов
		for (auto& el : *lst2)
			el.m_weight = el.m_weight + (*h)[el.m_from] - (*h)[el.m_to];

		gr.reset(new Graph(*lst2));

		// Дейкстра для каждой вершины
		for (int i = 0; i < sizem; i++)
		{
			U_PTR(VertexArr) prev;
			U_PTR(VertexArr) column;
			Dijkstra(gr, i, 0, column, prev);
			(*_dist)[i] = *column;

			// учитываем метки
			for (int j = 0; j < sizem; j++)
			{
				if ((*_dist)[i][j] != INF)
					(*_dist)[i][j] = (*_dist)[i][j] + (*h)[j] - (*h)[i];
			}
		}
		return 0;
	}

	// Эвристики
	// Манхэттенское расстояние
	inline Weight Manhattan(const Cell& _c1, const Cell& _c2)
	{
		return abs(_c1.GetX() - _c2.GetX()) + abs(_c1.GetY() - _c2.GetY());
	}

	// Расстояние Чебышева
	inline Weight Chebyshev(const Cell& _c1, const Cell& _c2)
	{
		return std::max(abs(_c1.GetX() - _c2.GetX()), abs(_c1.GetY() - _c2.GetY()));
	}

	// Евклидово расстояние
	inline Weight Euclid(const Cell& _c1, const Cell& _c2)
	{
		return Weight(sqrt(pow(_c2.GetX() - _c1.GetX(), 2) + pow(_c2.GetY() - _c1.GetY(), 2)));
	}

	// восстановление пути для А*
	inline CellVector ReconstructPath(
		const CellMatrix& _came_from,	// матрица педшествующих клеток
		const Cell& _end				// конец пути
	)
	{
		// конечный путь
		CellVector path;

		// проходим весь путь с конца к началу
		Cell cur_cell = _end;
		do {
			path.push_back(cur_cell);
			cur_cell = _came_from[cur_cell.GetX()][cur_cell.GetY()];
		} while (cur_cell != Cell());
		// TODO можно сделать List заместо vector, чтобы в
		// массиве делат push_front (не надо будет потом вызывать reverse)
		// инвертируем путь
		std::reverse(path.begin(), path.end());
		return path;
	}

	// расстояние между клетками
	inline Weight CellDist(
		const Cell& _c1,
		const Cell& _c2,
		const Map& _map
	)
	{
		return Manhattan(_c1, _c2) +
			abs(_map.GetCellHeight(_c1) - _map.GetCellHeight(_c2));
	}

	// Алгоритм А*
	inline Weight AStar(
		const U_PTR(Map)& _map,   // карта весов
		U_PTR(CellVector)& _dist, // кратчайшее расстояние
		U_PTR(VisitedCell)& _used,// посещенные клетки
		const Cell& _start,       // начальная клетка
		const Cell& _end,         // конечная клетка
		Weight(*h)(const Cell&, const Cell&), // эвристическая функция
		bool& path_found          // найден ли путь
	)
	{
#define SX _start.GetX()
#define SY _start.GetY()

		path_found = 0;

		// размер карты
		size_t msize = _map->GetSize();

		// отчищаем вектор кратчайшего расстояния
		_dist.reset();

		// матрица пройденных клеток
		_used = std::make_unique<VisitedCell>(msize, VisitedVert(msize, 0));

		// очередь рассматриваемых вершин
		std::priority_queue<WeightedCell, WeightedCellVector, WeightedCellGreater> q;

		// добавляем начальную клетку
		q.push(std::make_pair(0, _start));

		// матрица ячеек, из которых пришли
		CellMatrix came_from(msize, CellVector(msize, Cell()));

		// стоимость кратчайшего пути от _start в текущую
		WeightMatrix g_score(msize, WeightVector(msize, INF));
		g_score[SX][SY] = 0;

		// стоимость кратчайшего пути от _start в текущую
		// с учетом эвристики
		WeightMatrix f_score(msize, WeightVector(msize, INF));
		// TODO на сайте тут стоит h(_begin, _end)
		f_score[SX][SY] = 0;

		// пока очередь не пустая
		while (!q.empty())
		{
#define CCX cur.second.GetX()
#define СCY cur.second.GetY()
			// выбираем клетку с минимальным весов 
			WeightedCell cur = q.top();
			(*_used)[CCX][СCY] = true;
			q.pop();
			// если соседняя вершина - конечная
			if (cur.second == _end)
			{
				path_found = 1;
				_dist = std::make_unique<CellVector>(ReconstructPath(came_from, _end));
				return g_score[_end.GetX()][_end.GetY()];
			}

			// получаем список соседей
			NeighborsList nlst = _map->neighbors(cur.second);

			// для каждого соседа ищем кратчайше расстояние
			for (auto& el : nlst)
			{
#define NC el.second
#define NCX NC.GetX()
#define NCY NC.GetY()

				// расстояние от _start до текущего соседа через текущую вершину
				Weight temp_g_score =
					g_score[CCX][СCY] + CellDist(cur.second, NC, *_map);

				if (temp_g_score < g_score[NCX][NCY])
				{
					// обновляю родителя для текущей вершины
					came_from[NCX][NCY] = cur.second;

					// обновляю кратчайший путь в текущую вершину
					g_score[NCX][NCY] = temp_g_score;

					// обновляю кратчайший путь до соседа с учетом эвристики
					f_score[NCX][NCY] = g_score[NCX][NCY] + h(NC, _end);
					// если сосед не был пройден ранее,
					// добавляем его в очередь
					if (!(*_used)[NCX][NCY])
					{
						q.push(std::make_pair(f_score[NCX][NCY], NC));
						(*_used)[NCX][NCY] = true;
					}
				}
			}
		}

#undef NC
#undef NCX
#undef NCY
#undef СCX
#undef СCY
#undef SX
#undef SY
		return g_score[_end.GetX()][_end.GetY()];
	}
}

#endif // !ALGORITHMS_HPP
