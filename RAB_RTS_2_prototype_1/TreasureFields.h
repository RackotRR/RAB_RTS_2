#pragma once 
#include <string>
class ContentField;
class PlayerTreasures;

class TreasureFields {
public:
	TreasureFields(PlayerTreasures* treasures, int fieldH, int fieldW);
	~TreasureFields();

	// ���������� ���������� � ����� ��������� ������
	void UpdateTreasureFields();

	// ���������� ���������� � ����� � ����� ����
	void UpdateTreasureFields(const std::string& gold, const std::string& buildingRes, const std::string& fuel);
	 
	// ������� �� �����
	void GenerateOutput();
private: 
	ContentField* treasureFields[3]; 
	PlayerTreasures* treasures;
};