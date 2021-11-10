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
	if (contextMenus.empty()) return; // если нет активных меню, то выходим

	std::vector<Vector2> toDelete; // вектор для удаления меню
	for (auto& iter : contextMenus) {
		if (iter.second->GetContextObject() != selectedObject->GetPosition() || !selectedObject->IsSmthSelected())
			iter.second->Hide(); // если был изменён выбор, то меню следует закрыть

		if (iter.second->Update()) // обновляем меню
			toDelete.push_back(iter.first); // если его надо удалить, то заносим в вектор
	}
	for (auto& iter : toDelete) { // проходим по списку удаления
		delete contextMenus[iter]; // удаляем меню
		contextMenus.erase(iter); // удаляем его и из контейнера
	}
}

bool PlayerContextMenus::ProcessInput(const RRMouse& mouseState) {
	if (contextMenus.empty()) return false; // если нет активных меню, то выходим

	// поочерёдно вызываем обработку ввода для меню
	for (auto& iter : contextMenus) {
		if (iter.second->ProcessInput(mouseState)) 
			return true; // если что-то было выбрано
	}
	return false; // если ничего не выбрали
}


/*
	переделать всю эту жесть 
*/
void PlayerContextMenus::ShowContextMenu() {
	if (auto iter = contextMenus.find(selectedObject->GetPosition()); iter != contextMenus.end())
		return;  // если контекстное меню для такого объекта уже существует, то не будем его создавать

	const int menuHeight = 128;

	// добавляем контекстное меню в зависимости от типа выбранного объекта
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
			// будут различия между своим объектом и чужим
			contextMenus[selectedObject->GetPosition()] = new
				BuildingContextMenu(menuHeight, world->GetBuildingAt(selectedObject->GetPosition()), player);
		}
		break;
	case ObjectType::unit:
		if (world->GetUnitAt(selectedObject->GetPosition())->GetType() == UnitType::worker)
			contextMenus[selectedObject->GetPosition()] = new 
			WorkerContextMenu(menuHeight, static_cast<Worker*>(world->GetUnitAt(selectedObject->GetPosition())), player);
		else
			// будут различия между своим объектом и чужим
			contextMenus[selectedObject->GetPosition()] = new 
			UnitContextMenu(menuHeight, world->GetUnitAt(selectedObject->GetPosition()), player);
		break;
	}
}