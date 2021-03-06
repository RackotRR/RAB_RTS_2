#include <iostream>
#include <algorithm> 

#include "Player.h"
#include "GameIO.h"
#include "RRGamePlay.h"
#include "PlayerOutput.h"  
#include "PlayerData.h"
#include "Vector2.h"
#include "Rectangle.h"  
#include "Pathfinder.h" 
#include "World.h" 
#include "Objects.h"

#include "ContextMenu.h"
#include "ResourceContextMenu.h"
#include "BuildingContextMenu.h"
#include "UnitContextMenu.h"
#include "WorkerContextMenu.h"

#include "SelectedObject.h"
#include "SelectPlace.h"
#include "TreasureFields.h"
#include "PlayerContextMenus.h"
#include "MovingObjectsQueue.h"
#include "Camera.h"
#include "ObjectsFactory.h"

#include "TaskProduce.h" 
   
Player::Player(RRGamePlay* game, PlayerData* playerData) : 
	gameIO{ GameIO::Instance() },
	gameplay{ game },
	world{ game->GetWorld() },
	selectedObject{ world },
	selectPlace{ camera, world },
	contextMenus{ selectedObject, world, this },
	movingObjectsQueue{ world, this },
	playerData{ playerData },
	playerOutput{ this, game, world->GetLevel()->size }
{}
 
void Player::GenerateOutput() { 
	playerOutput.DrawWorld();

	if (selectedObject.IsSmthSelected()) // ���� ���-�� �������, �� ����� ��� ����������
		playerOutput.DrawSelectedObject();


	selectPlace.GenerateOutput();

	contextMenus.GenerateOutput();

	playerOutput.DrawTreasureFields();
}
 
bool Player::IsActorVisible(const Vector2& pos) const {
	return playerData->Visibility()(pos.X, pos.Y);
} 
     
void Player::Update() {   
	UpdateFinishingTurn();
	 
	contextMenus.Update();  
}
 
void Player::UpdateFinishingTurn() { 
	if (finished &&  // ������ ������ ����� ����
		playerState == PlayerState::common && // ����������� ��������
		!movingObjectsQueue.IsEmpty()) // �� �������� �����, ������� ������ ��������
	{  
		movingObjectsQueue.UpdateMovingQueue();
	}
}
 

void Player::UpdateSelectingPlace(const RRMouse& mouseState) {
	if (mouseState.Click(MouseButton::left)) { 
		if (selectPlace.ProcessInput(mouseState)) { // ���� ������� ����� ��� �������������  
			// ��������� ���� ������ ���������� ���������. ��� ������ ���� �������
			Unit* ptr = world->GetUnitAt(selectedObject.GetPosition());
			assert(ptr->GetType() == UnitType::worker); // ���� ��� �� ���, �� ���� ����������
			// �������� ��������� ���� ������������ ��� ����, ����� ������ �������
			if (ptr->TryToSpendMovePoints()) { 
				// ��� ������������� ����� ���������� � �������� � �������������
				auto treasures = playerData->Treasures();
				auto researches = playerData->Researches(); 
				// ������� ��� ������, ������� �������� � ������
				auto task = static_cast<TaskBuild<BuildingType>*>(ptr->CurrentTask());
				BuildingType buildingType = task->GetObjectType();
				// �������� ��������� ������� �� �������������
				if (treasures->Transaction(researches->GetPrice(buildingType))) { 
					// � ��������� ����� ������ �� �����
					ObjectsFactory::Instance()->MakeBuilding(selectPlace.GetPlace(), this, buildingType);

					// ������������� ���� ������������� � ���������� �������� �������
					task->SetPosition(selectPlace.GetPlace());

					TaskBuildProduction* taskBuildProduction = new TaskBuildProduction(*task); 
					ptr->SetTask(taskBuildProduction); 
				}  
				else { // ��� ��������
					ptr->FailedTask();
				}
			}
			else { // ��� ����� ������������
				ptr->FailedTask();
			}
		} 
		// � ����� ������, ����� ��� ������������� � ������� �����
		selectPlace.ClearPlacesToSelect();
		selectedObject.SelectNothing();
		SwitchState(PlayerState::common);  
	}
	if (mouseState.Click(MouseButton::right)) {
		// ����� ��� ������������� � ������� �����
		selectPlace.ClearPlacesToSelect();
		selectedObject.SelectNothing();
		SwitchState(PlayerState::common);
	}
}
 
void Player::UpdateCommonState(const RRMouse& mouseState, const KeyboardState& keyState) { 
	if (keyState.Click(Keys::ENTER)) {
		// ��������� �������� ���������� ����
		FinishTurn();
	}
	if (mouseState.Click(MouseButton::left)) {
		if (contextMenus.ProcessInput(mouseState)) return;
	//	if (selectPlace->ProcessInput(mouseState)) return;
		TryToSelect(mouseState); // ����� ������� - �� ����� �������������� ������������ � ������� � ����
	}
	if (mouseState.Click(MouseButton::right)) {
		// ���� ���-�� �������, �� ���������� ���������� ���
		if (selectedObject.IsSmthSelected()) {
			TryToMove(mouseState);
		}
		// � ����� ������, ��� �������� ������ ������
		selectedObject.SelectNothing(); 
	}
}

void Player::ProcessInput(const RRMouse& mouseState, const KeyboardState& keyState) { 
	switch (playerState)
	{
	case PlayerState::common:
		camera.Update();
		UpdateCommonState(mouseState, keyState);
		break;
	case PlayerState::moveAnimation:
		camera.Update();
		break;
	case PlayerState::selectingPlace:
		UpdateSelectingPlace(mouseState);
		break; 
	default:
		break;
	} 
}
 
void Player::StartTurn() {
	selectedObject.SelectNothing();
	finished = false;  
}
void Player::FinishTurn() { 
	finished = true;   
	movingObjectsQueue.BuildMovingQueue(TaskType::move);
}

void Player::TryToMove(const RRMouse& mouseState) {
	ObjectType type = selectedObject.GetType();
	if (type != ObjectType::unit) return; // ������������� ����� ������ �����

	Unit* ptr = world->GetUnitAt(selectedObject.GetPosition());
	if (ptr->GetMaster() != this) return; // ����������� ����� ������ ���� �����

	// �������, ���� �������
	Vector2 pos = TransofrmCoordinates(Vector2(mouseState.Position.X, mouseState.Position.Y), camera); 

	if (!IsPositionSuitable(pos, world->GetLevel()->size)) return; // ������� �� ��������� ����� 
	if (!IsActorVisible(pos)) return; // ������� �� ��������� ������� �������

	// �������� ������ ������ ����� ����, ���� �������
	gameplay->Move(ptr, pos); 

}
void Player::TryToSelect(const RRMouse& mouseState) {
	Vector2 pos = TransofrmCoordinates(Vector2(mouseState.Position.X, mouseState.Position.Y), camera);
	selectedObject.Select(pos);
	 
	
	if (selectedObject.IsSmthSelected())
		if (IsActorVisible(pos)) {// ���� ���-�� ������� � �� ��, �� ���������� ����������� ����
			contextMenus.ShowContextMenu();
		}
		else { // ���� ������ ������, �� ��� �� �����, �� ������� ���������
			selectedObject.SelectNothing();
		} 
}
     
bool Player::Finished() const {
	return finished && // ���� ������ ������ ���������� ����
		playerState == PlayerState::common && // ����������� ��� ��������
		movingObjectsQueue.IsEmpty(); // ��� ����� ��������� ������
}
void Player::SwitchState(PlayerState state) {
	playerState = state;
}
PlayerState Player::GetPlayerState() const {
	return playerState;
}
 
RRGamePlay* Player::GetRRGamePlay() {
	return gameplay;
}
const SelectedObject& Player::GetSelectedObject() {
	return selectedObject;
} 
PlayerData* Player::GetPlayerData() {
	return playerData;
}
const Camera& Player::GetCamera() const {
	return camera;
}

void Player::Worker_Build(Worker* worker) {
	// ���� ��� ������ �� �������������, �� ��������� ������ � ������ ����� ������
	assert(worker->CurrentTask()->GetType() == TaskType::build);
	// ����������� ������
	auto task = static_cast<TaskBuild<BuildingType>*>(worker->CurrentTask());
	   
	// ����� �� ����� ���������� �������� ��� �������������  
	if (!playerData->Treasures()->Have(playerData->Researches()->GetPrice(task->GetObjectType()))) {
		worker->FailedTask(); // ���� �� �����, �� ������ �� ���������
		selectedObject.SelectNothing();
		return;
	}

	// ������� ����� � 4 �������� �������, ����� � �������
	selectPlace.InitializePlaces(worker->GetPosition()); // �������� ������ �����
	if (selectPlace.IsEmpty()) { // ���� ����� ��� ��������� ������, �� ������ �����������
		worker->FailedTask(); 
		selectedObject.SelectNothing();
		return;
	}
	 
	// �� �� => ����������� ��������� ������ �� ����� ����� ��� �������������
	SwitchState(PlayerState::selectingPlace); 
} 

void Player::Worker_Become(Worker* worker) {
	// ���� ��� ������ �� �������������, �� ��������� ������ � ������ ����� ������
	assert(worker->CurrentTask()->GetType() == TaskType::build);

	// ����������� ������
	auto task = static_cast<TaskBuild<UnitType>*>(worker->CurrentTask());

	// �������� ��������� �� �������������
	if (playerData->Treasures()->Transaction(playerData->Researches()->GetPrice(task->GetObjectType()))) {
		// ���� �������� �������, �� ������ �� ����� �������� ����� ���� 
		ObjectsFactory::Instance()->MakeUnitAndReplace(worker, task->GetObjectType());
	}
	else { 
		worker->FailedTask(); // ���� �� ����������, �� ���������� ������ 
	}

	selectedObject.SelectNothing();
}
 
void Player::House_Produce(House* house) {
	// ���� ��� ������ �� ������ ������������, �� ��������� ������ � ������ ����� ������
	assert(house->CurrentTask()->GetType() == TaskType::produceStart); 
	 
	// ����������� ������
	auto task = static_cast<TaskProduceStart<Worker>*>(house->CurrentTask());

	if (playerData->Treasures()->Transaction(playerData->Researches()->GetPrice(UnitType::worker))) {
		// ���� �������� �������, �� ������ ��� ������ �� ��������� ������������ 
		house->SetTask(new TaskProduce<Worker>(task->GetValueToFinish()));
	}
	else {
		house->FailedTask();
	}

	selectedObject.SelectNothing();
}