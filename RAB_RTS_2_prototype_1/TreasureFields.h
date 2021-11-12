#pragma once 
#include <string>

class ContentField;
class PlayerTreasures;

class TreasureFields {
public:
	TreasureFields(PlayerTreasures* treasures, int fieldH, int fieldW);
	~TreasureFields();

	// обновление информации во всех полях
	void UpdateTreasureFields();

	// заполнение информации в полях в явном виде
	void FillTreasureFields(std::string gold, std::string buildingRes, std::string fuel);
	 
	// вывести на экран
	void GenerateOutput();
private:  
	// предыдущие значения ресурсов
	int prevGold;
	int prevBuildingRes;
	int prevFuel;

	ContentField* treasureFields[3]; 
	PlayerTreasures* treasures;

	// если изменился ресурс, обновить поле
	void UpdateGoldField();
	void UpdateBuildingResField();
	void UpdateFuelField();
};