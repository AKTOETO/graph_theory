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

}


#endif // !ALGORITHMS_HPP
