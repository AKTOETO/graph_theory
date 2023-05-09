#ifndef PRESETGRAPHMANT3_h
#define PRESETGRAPHMANT3_h

#include "../base/BasePresetGraphMan.hpp"

class PresetGraphManT3 :
   virtual public BaseGraphManager
{
protected:


public:
	// конструктор и деструктор
	PresetGraphManT3(const S_PTR(Graph)& _graph, const S_PTR(std::vector<bool>) _states);
	~PresetGraphManT3() override;

	//==================================//
	//         CALCULATE МЕТОДЫ         //
	//==================================//

	// расчет: мосты в графе

	// расчет: шарниры в графе

	// расчет: мосты в диграфе

	// расчет: шарниры в диграфе

	//==================================//
	//            GET МЕТОДЫ            //
	//==================================//

	// получение: мосты в графе 

	// получение: шарниры в графе 

	// получение: мосты в диграфе 

	// получение: шарниры в диграфе 

};


#endif // !PRESETGRAPHMANT3_h
