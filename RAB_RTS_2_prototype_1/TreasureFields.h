#pragma once 
#include <string>

class ContentField;
class PlayerTreasures;

class TreasureFields {
public:
	TreasureFields(PlayerTreasures* treasures, int fieldH, int fieldW);
	~TreasureFields();

	// ���������� ���������� �� ���� �����
	void UpdateTreasureFields();

	// ���������� ���������� � ����� � ����� ����
	void FillTreasureFields(std::string gold, std::string buildingRes, std::string fuel);
	 
	// ������� �� �����
	void GenerateOutput();
private:  
	// ���������� �������� ��������
	int prevGold;
	int prevBuildingRes;
	int prevFuel;

	ContentField* treasureFields[3]; 
	PlayerTreasures* treasures;

	// ���� ��������� ������, �������� ����
	void UpdateGoldField();
	void UpdateBuildingResField();
	void UpdateFuelField();
};