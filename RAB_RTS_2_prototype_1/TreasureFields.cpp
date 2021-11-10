#include "TreasureFields.h"
#include "ContentField.h"
#include "PlayerTreasures.h" 
#include "RRTextureManager.h"

TreasureFields::TreasureFields(PlayerTreasures* treasures, int fieldH, int fieldW) :  
	treasures(treasures)
{ 
	int space = 10;

	// добавляем поля
	// Gold
	ContentField* field = new ContentField(Rectangle{ 0, 0, fieldW, fieldH });
	field->SetTexture(RRTextureManager::Instance()->GetTexture(TextureType::goldIcon));
	treasureFields[0] = field;

	// BuildingRes
	field = new ContentField(Rectangle{ fieldW + space, 0, fieldW, fieldH });
	field->SetTexture(RRTextureManager::Instance()->GetTexture(TextureType::buildingResIcon));
	treasureFields[1] = field;

	// Fuel
	field = new ContentField(Rectangle{ 2 * (fieldW + space), 0, fieldW, fieldH });
	field->SetTexture(RRTextureManager::Instance()->GetTexture(TextureType::fuelIcon));
	treasureFields[2] = field;

	// заполняем поля данными о ресурсах
	UpdateTreasureFields();
}

TreasureFields::~TreasureFields() {
	for (auto iter : treasureFields)
		delete iter;
}

void TreasureFields::UpdateTreasureFields() { 
	// вызываем перегруженную версию метода с параметрами по умолчанию
	UpdateTreasureFields(
		std::to_string(treasures->GetGold()),
		std::to_string(treasures->GetBuildingRes()),
		std::to_string(treasures->GetFuel())
	);
}

void TreasureFields::UpdateTreasureFields(const std::string& gold, const std::string& buildingRes, const std::string& fuel) {
	treasureFields[0]->SetText(gold);
	treasureFields[1]->SetText(buildingRes);
	treasureFields[2]->SetText(fuel);
} 

void TreasureFields::GenerateOutput() { 
	for (auto iter : treasureFields) 
		iter->GenerateOutput();
}