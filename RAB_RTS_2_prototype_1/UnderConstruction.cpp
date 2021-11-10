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
	if (underConstruction >= toConstruct) { // ���� ������ ���� ���������
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
	if (!building) return; // ���� ������ �� �����������, �� ������ ������������� ��������
	double quotient = underConstruction * 1.0 / toConstruct; // ������� ����������
	if (quotient >= 1) {
		building->ChangeCurrentTexture(0); // ��������� ����������� ������
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