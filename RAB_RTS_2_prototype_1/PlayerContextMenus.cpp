#include "PlayerContextMenus.h"
#include "SelectedObject.h"
#include "World.h"
#include "Objects.h"

#include "ContextMenu.h"
#include "ResourceContextMenu.h"
#include "BuildingContextMenu.h"
#include "UnitContextMenu.h"
#include "WorkerContextMenu.h"
#include "HouseContextMenu.h"

PlayerContextMenus::PlayerContextMenus(SelectedObject* selectedObject, World* world, Player* player) :
	world(world),
	selectedObject(selectedObject),
	player(player)
{ 
}

PlayerContextMenus::~PlayerContextMenus() {
	for (auto& iter : contextMenus)
		delete iter.second;
}

void PlayerContextMenus::GenerateOutput() {
	for (auto& iter : contextMenus) {
		iter.second->GenerateOutput();
	}
}

void PlayerContextMenus::Update() {
	if (contextMenus.empty()) return; // ���� ��� �������� ����, �� �������

	std::vector<Vector2> toDelete; // ������ ��� �������� ����
	for (auto& iter : contextMenus) {
		if (iter.second->GetContextObject() != selectedObject->GetPosition() || !selectedObject->IsSmthSelected())
			iter.second->Hide(); // ���� ��� ������ �����, �� ���� ������� �������

		if (iter.second->Update()) // ��������� ����
			toDelete.push_back(iter.first); // ���� ��� ���� �������, �� ������� � ������
	}
	for (auto& iter : toDelete) { // �������� �� ������ ��������
		delete contextMenus[iter]; // ������� ����
		contextMenus.erase(iter); // ������� ��� � �� ����������
	}
}

bool PlayerContextMenus::ProcessInput(const RRMouse& mouseState) {
	if (contextMenus.empty()) return false; // ���� ��� �������� ����, �� �������

	// ��������� �������� ��������� ����� ��� ����
	for (auto& iter : contextMenus) {
		if (iter.second->ProcessInput(mouseState)) 
			return true; // ���� ���-�� ���� �������
	}
	return false; // ���� ������ �� �������
}


/*
	���������� ��� ��� ����� 
*/
void PlayerContextMenus::ShowContextMenu() {
	if (auto iter = contextMenus.find(selectedObject->GetPosition()); iter != contextMenus.end())
		return;  // ���� ����������� ���� ��� ������ ������� ��� ����������, �� �� ����� ��� ���������

	const int menuHeight = 128;

	// ��������� ����������� ���� � ����������� �� ���� ���������� �������
	switch (selectedObject->GetType()) {
	case ObjectType::resource:
	{
		auto res = world->GetResourceAt(selectedObject->GetPosition());
		contextMenus[selectedObject->GetPosition()] = new 
			ResourceContextMenu(menuHeight, res->GetPosition(), res->GetMaxValue(), res->GetValue());
	};
	break;
	case ObjectType::building:
		if (world->GetBuildingAt(selectedObject->GetPosition())->GetType() == BuildingType::house) {
			contextMenus[selectedObject->GetPosition()] = new
				HouseContextMenu(menuHeight, static_cast<House*>(world->GetBuildingAt(selectedObject->GetPosition())), player);
		}
		else {
			// ����� �������� ����� ����� �������� � �����
			contextMenus[selectedObject->GetPosition()] = new
				BuildingContextMenu(menuHeight, world->GetBuildingAt(selectedObject->GetPosition()), player);
		}
		break;
	case ObjectType::unit:
		if (world->GetUnitAt(selectedObject->GetPosition())->GetType() == UnitType::worker)
			contextMenus[selectedObject->GetPosition()] = new 
			WorkerContextMenu(menuHeight, static_cast<Worker*>(world->GetUnitAt(selectedObject->GetPosition())), player);
		else
			// ����� �������� ����� ����� �������� � �����
			contextMenus[selectedObject->GetPosition()] = new 
			UnitContextMenu(menuHeight, world->GetUnitAt(selectedObject->GetPosition()), player);
		break;
	}
}