#ifndef DSU_H
#define DSU_H

// Для алгоритма Борувки
struct Subset
{
	int m_parent;
	int m_rank;
};

// система непересекающихся множеств DSU (disjoint set union)
// сжатие пути + ранговая эвристика
class DSU
{
private:

	Subset* m_subsets;
public:

	// Запрект конструктора по умолчанию
	DSU() = delete;

	// конструктор, принимающий количество 
	// элементов в системе множеств
	DSU(size_t _size);

	// деструктор
	~DSU();

	// добавдение элемента m_x,
	// помещая его в новое множество
	void MakeSet(int m_x);

	// поиск множества,в котором содержится 
	// переданный в функцию элемент
	int FindSet(int i);

	// объединение множеств по рангу
	void UnionSet(int m_x, int m_y);
};

#endif //!DSU_H
