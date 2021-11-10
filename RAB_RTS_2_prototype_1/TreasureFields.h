#pragma once 
#include <string>
class ContentField;
class PlayerTreasures;

class TreasureFields {
public:
	TreasureFields(PlayerTreasures* treasures, int fieldH, int fieldW);
	~TreasureFields();

	// обновление информации в полях ресурсами игрока
	void UpdateTreasureFields();

	// обновление информации в полях в явном виде
	void UpdateTreasureFields(const std::string& gold, const std::string& buildingRes, const std::string& fuel);
	 
	// вывести на экран
	void GenerateOutput();
private: 
	ContentField* treasureFields[3]; 
	PlayerTreasures* treasures;
};