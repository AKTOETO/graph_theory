#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "PresetsManangers/MajorGraphManPreset.h"

class GraphManager
{
protected:
	U_PTR(MajorGraphManPreset) m_major_preset;

	S_PTR(Graph) m_graph;
	S_PTR(State) m_states;

public:
	GraphManager(std::string _filepath, INPUT_FILE_TYPE _in_f_type);
	~GraphManager();

	const U_PTR(MajorGraphManPreset)& GetMajorPreset() const;
};

#endif //GRAPHMANAGER_H
