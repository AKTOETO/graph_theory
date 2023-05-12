#ifndef PRESETGRAPHMANT4_h
#define PRESETGRAPHMANT4_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT4 :
	virtual public BaseGraphPresetManager
{
protected:
	// остовное дерево для Крускала
	U_PTR(EdgeList) m_cruscal_spanning_tree;

	// остовное дерево для Прима
	U_PTR(EdgeList) m_prim_spanning_tree;

	// остовное дерево для Борувки
	U_PTR(EdgeList) m_boruvka_spanning_tree;

public:
	// конструктор и деструктор
	PresetGraphManT4(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states);
	~PresetGraphManT4() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//


	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//


};


#endif // !PRESETGRAPHMANT4_h
