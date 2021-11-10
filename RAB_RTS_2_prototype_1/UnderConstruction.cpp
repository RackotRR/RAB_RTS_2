#include "UnderConstruction.h"
#include <assert.h>
#include "Building.h"
 
int UnderConstruction::GetUnderConstruction() const {
	return toConstruct - underConstruction;
}

bool UnderConstruction::Construct(int val) {
	assert(val >= 0 && GetUnderConstruction());

	underConstruction += val;
	UpdateTexture();
	if (underConstruction >= toConstruct) { // если здание было построено
		return true;
	}
	else {
		return false;
	}
}

void UnderConstruction::SetPointsToConstruct(int toConstruct, Building* building) {
	assert(toConstruct >= 0);

	this->toConstruct = toConstruct;
	this->building = building;
	UpdateTexture();
}

void UnderConstruction::UpdateTexture() { 
	if (!building) return; // если здание не предоставли, то некуда устанавливать текстуры
	double quotient = underConstruction * 1.0 / toConstruct; // процент готовности
	if (quotient >= 1) {
		building->ChangeCurrentTexture(0); // полностью отстроенное здание
	}
	else if (quotient >= 0.75) {
		building->ChangeCurrentTexture(4);
	}
	else if (quotient >= 0.5) {
		building->ChangeCurrentTexture(3);
	}
	else if (quotient >= 0.25) {
		building->ChangeCurrentTexture(2);
	}
	else {
		building->ChangeCurrentTexture(1);
	}
}