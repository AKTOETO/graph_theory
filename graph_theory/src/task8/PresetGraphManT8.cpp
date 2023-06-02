#include "../pch.h"
#include "PresetGraphManT8.h"

PresetGraphManT8::PresetGraphManT8(
	const S_PTR(SystemSetting)& _settings,
	const S_PTR(Graph)& _graph,
	const S_PTR(StateVector) _states
) :// инициализация всех полей
	BaseGraphPresetManager(_settings, _graph, _states),
	m_map(std::make_unique<Map>(m_sys_settings->m_filepath)),
	numb_of_heur(4),
	m_dist(numb_of_heur),
	m_used_cell(numb_of_heur),
	m_dist_length(std::make_unique<WeightVector>(numb_of_heur, -1))
{
	m_heur_func = {
		ALGO::Manhattan,
		ALGO::Chebyshev,
		ALGO::Euclid,
		[](const Cell&, const Cell&)->Weight { return 0; }
	};

	// проверка на корректность начальных точек
	if (
		m_sys_settings->m_begin.GetX() >= m_map->GetSize() ||
		m_sys_settings->m_begin.GetX() < 0 ||
		m_sys_settings->m_begin.GetY() >= m_map->GetSize() ||
		m_sys_settings->m_begin.GetY() < 0 ||
		m_sys_settings->m_end.GetX() >= m_map->GetSize() ||
		m_sys_settings->m_end.GetX() < 0 ||
		m_sys_settings->m_end.GetY() >= m_map->GetSize() ||
		m_sys_settings->m_end.GetY() < 0
		)
		ERROR("Точки выходят за карту!");
}

PresetGraphManT8::~PresetGraphManT8()
{
}

bool PresetGraphManT8::CalculateAStarShortestPath()
{
	// цикл по 4ем эвристикам
	for (int i = 0; i < numb_of_heur; i++)
	{
		bool is_found = 0;
		(*m_dist_length)[i] = ALGO::AStar(
			m_map, m_dist[i], m_used_cell[i],
			m_sys_settings->m_begin, m_sys_settings->m_end,
			m_heur_func[i], is_found
		);
		if (!is_found)
		{
			ERROR("Путь не найден. i = " + std::to_string(i));
			return false;
		}
	}
	return true;
}

bool PresetGraphManT8::CalculateAStarShortestPathLength()
{
	IF_ST_SHOULD_BE_CALC(SPEC::T8_PATH, CalculateAStarShortestPath());
	IF_ST_CALC(SPEC::T8_PATH)
		return true;

	return false;
}

const std::vector<S_PTR(CellVector)>& PresetGraphManT8::GetAStarShortestPath() const
{
	return m_dist;
}

const WeightVector& PresetGraphManT8::GetAStarShortestPathLength() const
{
	return *m_dist_length;
}

const std::vector<double> PresetGraphManT8::GetAStarPercentUsedCells() const
{
	std::vector<double> out(numb_of_heur);
	for (int i = 0; i < numb_of_heur; i++)
	{
		out[i] = 0;
		std::for_each((*m_used_cell[i]).begin(), (*m_used_cell[i]).end(),
			[&](const VisitedVert& _vec)
			{
				out[i] += std::count_if(_vec.begin(), _vec.end(), [](const bool& _val)
					{
						return _val == 1;
					}
				);
			}
		);
		out[i] /= (m_map->GetSize() * m_map->GetSize());
		out[i] *= 100.0;
	}

	return out;
}
