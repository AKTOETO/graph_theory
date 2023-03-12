#include "Graph.h"

void Graph::ReadGraphFromFile(std::ifstream& _ifstream)
{
	// своровать все из старого проекта по структурам данных
}

Graph::Graph(std::string _filepath)
{
	INFO("создание графа");
}

Graph::~Graph()
{
}

int Graph::weight(Vertex _vi, Vertex _vj) const
{
	return 0;
}

bool Graph::is_edge(Vertex _vi, Vertex _vj) const
{
	return false;
}

const VertexMatrix& Graph::adjacency_matrix() const
{
	return m_adjacency_matrix;
}

VertexArr Graph::adjacency_list(Vertex _v) const
{
	return VertexArr();
}

EdgeArr Graph::list_of_edges() const
{
	return EdgeArr();
}

EdgeArr Graph::list_of_edges(Vertex _v) const
{
	return EdgeArr();
}

bool Graph::is_directed() const
{
    return false;
}
