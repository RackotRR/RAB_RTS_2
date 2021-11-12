#include "TreasureFields.h"
#include "ContentField.h"
#include "PlayerTreasures.h" 
#include "RRTextureManager.h"

TreasureFields::TreasureFields(PlayerTreasures* treasures, int fieldH, int fieldW) :  
	treasures{ treasures }
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

// обновление информации во всех полях
void TreasureFields::UpdateTreasureFields() {  
	UpdateGoldField();
	UpdateBuildingResField();
	UpdateFuelField();
}

// заполнение информации в полях в явном виде
void TreasureFields::FillTreasureFields(std::string gold, std::string buildingRes, std::string fuel) {
	treasureFields[0]->SetText(std::move(gold));
	treasureFields[1]->SetText(std::move(buildingRes));
	treasureFields[2]->SetText(std::move(fuel));
} 

void TreasureFields::GenerateOutput() { 
	for (auto iter : treasureFields) 
		iter->GenerateOutput();
}

// если изменился ресурс, обновить поле
void TreasureFields::UpdateGoldField() {
	int gold = treasures->GetGold();

	if (gold != prevGold) {
		treasureFields[0]->SetText(std::to_string(gold));
		prevGold = gold;
	}
}

// если изменился ресурс, обновить поле
void TreasureFields::UpdateBuildingResField() {
	int buildingRes = treasures->GetBuildingRes();

	if (buildingRes != prevBuildingRes) {
		treasureFields[1]->SetText(std::to_string(buildingRes));
		prevBuildingRes = buildingRes;
	}
}

// если изменился ресурс, обновить поле
void TreasureFields::UpdateFuelField() {
	int fuel = treasures->GetFuel();

	if (fuel != prevFuel) {
		treasureFields[2]->SetText(std::to_string(fuel));
		prevFuel = fuel;
	}
}