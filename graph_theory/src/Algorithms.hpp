#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "Graph.h"

namespace ALGO
{
	// BFS ����� � ������
	inline void BFS(
		const S_PTR(Graph)& _graph,				// ����
		const U_PTR(VertexArr)& _marked_vert,	// ������ ������������� ������
		const int& _start_vert,					// ��������� ������� 
		const int& _numb_of_connetivity_comp	// ����� ���������� ���������
	)
	{
		INFO("BFS");

		// ������� ������� ������
		VertexQueue vert_q;
		// ���������� ��������� ������� � �������
		vert_q.push(_start_vert);
		// ����������� ��������� ������� ����� ���������� ���������,
		// � ������� ��� ��������� (��������� ��)
		(*_marked_vert)[_start_vert] = _numb_of_connetivity_comp;

		// ������� �������
		Vertex v;

		// ���� ������� �� ������
		// ������������ �������� �������
		while (!vert_q.empty())
		{
			// �������� ������� �������
			v = vert_q.front();
			vert_q.pop();

			// ���������� �� ���� ������� ��������
			for (const Vertex& ver : _graph->adjacency_list(v))
			{
				// ���� ������� �� �������������
				// ��������� �� � ������� � ���������
				if (!(*_marked_vert)[ver])
				{
					vert_q.push(ver);
					(*_marked_vert)[ver] = _numb_of_connetivity_comp;
				}
			}
		}
	}

	// DFS ����� � �������
	inline void DFS(
		const S_PTR(Graph)& _graph,				// ����
		const U_PTR(VertexArr)& _marked_vert,	// ������ ������������� ������
		const int& _start_vert,					// ��������� ������� 
		const int& _numb_of_connetivity_comp,	// ����� ���������� ���������
		const S_PTR(VertexList)& _order = NULL	// ������ ������ ��� �������������� ����������
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

			// ���� �� ���� ������� ������������ ��������
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

			// ���� ����� ���������� ������� _order 
			if (_order)
			{
				_order->push_back(vert);
			}
		}
	}

	// TopologicalSort �������������� ����������
	// ��������� ������ ������ � ������� ���������� ������� ������
	inline VertexList TopologicalSort(
		const S_PTR(Graph)& _graph	// ����
	)
	{
		INFO("�������������� ����������");

		// ������ ���������� ������
		U_PTR(VertexArr) used_vert = std::make_unique<VertexArr>(_graph->adjacency_matrix().size());

		// ������ ������, ����������� � ������� ���������� ������� ������
		S_PTR(VertexList) order = std::make_shared<VertexList>();

		// ���� �� ���� ������������ �������� �����
		for (int i = 0; i < used_vert->size(); i++)
		{
			if(!(*used_vert)[i])
			{
				DFS(_graph, used_vert, i, 1, order);
			}
		}

		// �������� �������
		std::reverse(order->begin(), order->end());

		return *order;
	}

}


#endif // !ALGORITHMS_HPP
