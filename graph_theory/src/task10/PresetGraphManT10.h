#ifndef PRESETGRAPHMANT10_h
#define PRESETGRAPHMANT10_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT10 :
	virtual public BaseGraphPresetManager
{
protected:

	// матрица остаточной пропускной способности
	S_PTR(VertexMatrix) m_bandwidth;

	// длина потока
	Weight m_max_flow_length;

	// источник
	Vertex m_source;

	// сток
	Vertex m_sink;

	// список ребер с пропускной способностью
	EdgeBandwidthList m_lst;

public:
	// конструктор и деструктор
	PresetGraphManT10(
		const S_PTR(SystemSetting)& _settings,
		const S_PTR(Graph)& _graph,
		const S_PTR(StateVector) _states
	);
	~PresetGraphManT10() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: Максимальный поток
	bool CalculateMaxFlow();

	// расчет: Длина потока
	bool CalculateFlowLength();

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: матрица остаточной пропускной способности
	const EdgeBandwidthList& GetBandwidth() const;

	// получение: Длина потока
	const Weight& GetFlowLength() const;

	// получение: Источник
	const Vertex& GetSource() const;

	// получение: Сток
	const Vertex& GetSink() const;
};

#endif // !PRESETGRAPHMANT10_h
