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

#include <iostream>
#include <algorithm>  
 

Player::Player()
	: gameIO(GameIO::Instance()),
	gameplay(nullptr),
	width(), height(), 
	playerOut(nullptr),
	playerData(nullptr),
	selectedObject(nullptr),
	selectPlace(nullptr),
	treasureFields(nullptr),
	contextMenus(nullptr),
	camera(nullptr),
	world(nullptr),
	movingObjectsQueue(nullptr),
	playerState(PlayerState::common)
{
}

bool Player::Initialize(RRGamePlay* game, PlayerData* playerData) {
	this->gameplay = game;
	this->playerData = playerData;
	this->world = gameplay->GetWorld();
	this->width = world->GetLevel()->width;
	this->height = world->GetLevel()->height;

	camera = new Camera();

	selectedObject = new SelectedObject(world);
	selectPlace = new SelectPlace(camera, world);

	playerOut = new PlayerOutput;
	playerOut->Initialize(this, game, width, height);

	treasureFields = new TreasureFields(playerData->Treasures(), 64, 192); 
	contextMenus = new PlayerContextMenus(selectedObject, world, this);

	movingObjectsQueue = new MovingObjectsQueue(world, this);

	return true;
}
 
void Player::Shutdown() { 
	delete movingObjectsQueue;

	delete contextMenus;

	delete treasureFields;
	
	delete selectedObject;

	delete playerOut;

	delete camera;
}
 
void Player::GenerateOutput() { 
	playerOut->DrawWorld();

	if (selectedObject->IsSmthSelected()) // если что-то выбрано, то нужно это нарисовать
		playerOut->DrawSelectedObject();


	selectPlace->GenerateOutput();

	contextMenus->GenerateOutput();

	treasureFields->GenerateOutput(); 
}
 
bool Player::IsActorVisible(const Vector2& pos) const {
	return playerData->Visibility()[pos.Y][pos.X];
} 
     
void Player::Update() {   
	UpdateFinishingTurn();
	 
	contextMenus->Update();  
}
 
void Player::UpdateFinishingTurn() { 
	if (finished &&  // нажали кнопку конца хода
		playerState == PlayerState::common && // закончились анимации
		!movingObjectsQueue->IsEmpty()) // но остались актёры, которые должны доходить
	{  
		movingObjectsQueue->UpdateMovingQueue();
	}
}
 

void Player::UpdateSelectingPlace(const RRMouse& mouseState) {
	if (mouseState.Click(MouseButton::left)) { 
		if (selectPlace->ProcessInput(mouseState)) { // если выбрали место для строительства  
			// выбранный юнит должен оставаться выбранным. это должен быть рабочий
			Unit* ptr = world->GetUnitAt(selectedObject->GetPosition());
			assert(ptr->GetType() == UnitType::worker); // если это не так, то надо исправлять
			// пытаемся потратить очко передвижения для того, чтобы начать строить
			if (ptr->TryToSpendMovePoints()) { 
				// для строительства нужна информация о ресурсах и исследованиях
				auto treasures = playerData->Treasures();
				auto researches = playerData->Researches(); 
				// смотрим тип здания, которое значится в задаче
				auto task = static_cast<TaskBuild<BuildingType>*>(ptr->CurrentTask());
				BuildingType buildingType = task->GetObjectType();
				// пытаемся потратить ресурсы на строительство
				if (treasures->Transaction(researches->GetPrice(buildingType))) {
					// если получилось, то обновляем таблички
					treasureFields->UpdateTreasureFields();
					// и добавляем новое здание на карту
					ObjectsFactory::Instance()->MakeBuilding(selectPlace->GetPlace(), this, buildingType);

					// устанавливаем цель строительства и заставляем рабочего строить
					task->SetPosition(selectPlace->GetPlace());

					TaskBuildProduction* taskBuildProduction = new TaskBuildProduction(*task); 
					ptr->SetTask(taskBuildProduction); 
				}  
				else { // нет ресурсов
					ptr->FailedTask();
				}
			}
			else { // нет очков передвижения
				ptr->FailedTask();
			}
		} 
		// в любом случае, после ЛКМ переключаемся в обычный режим
		selectPlace->Shutdown();
		selectedObject->SelectNothing();
		SwitchState(PlayerState::common);  
	}
	if (mouseState.Click(MouseButton::right)) {
		// после ПКМ переключаемся в обычный режим
		selectPlace->Shutdown();
		selectedObject->SelectNothing();
		SwitchState(PlayerState::common);
	}
}
 
void Player::UpdateCommonState(const RRMouse& mouseState, const KeyboardState& keyState) { 
	if (keyState.Click(Keys::ENTER)) {
		// запустить операцию завершения хода
		FinishTurn();
	}
	if (mouseState.Click(MouseButton::left)) {
		if (contextMenus->ProcessInput(mouseState)) return;
	//	if (selectPlace->ProcessInput(mouseState)) return;
		TryToSelect(mouseState); // выбор объекта - не будет обрабатываться одновременно с выбором в меню
	}
	if (mouseState.Click(MouseButton::right)) {
		// если что-то выбрано, то попытаемся перединуть это
		if (selectedObject->IsSmthSelected()) {
			TryToMove(mouseState);
		}
		// в любом случае, ПКМ означает снятие выбора
		selectedObject->SelectNothing(); 
	}
}

void Player::ProcessInput(const RRMouse& mouseState, const KeyboardState& keyState) { 
	switch (playerState)
	{
	case PlayerState::common:
		camera->Update();
		UpdateCommonState(mouseState, keyState);
		break;
	case PlayerState::moveAnimation:
		camera->Update();
		break;
	case PlayerState::selectingPlace:
		UpdateSelectingPlace(mouseState);
		break; 
	default:
		break;
	} 
}
 
void Player::StartTurn() {
	selectedObject->SelectNothing();
	finished = false;  
}
void Player::FinishTurn() { 
	finished = true;   
	movingObjectsQueue->BuildMovingQueue(TaskType::move);
}

void Player::TryToMove(const RRMouse& mouseState) {
	ObjectType type = selectedObject->GetType();
	if (type != ObjectType::unit) return; // передвигаться могут только юниты

	Unit* ptr = world->GetUnitAt(selectedObject->GetPosition());
	if (ptr->GetMaster() != this) return; // передвигать можно только свои юниты

	// смотрим, куда тыкнули
	Vector2 pos = TransofrmCoordinates(Vector2(mouseState.Position.X, mouseState.Position.Y), camera); 

	if (!IsPositionSuitable(pos, width, height)) return; // тыкнули за пределами карты 
	if (!IsActorVisible(pos)) return; // тыкнули за пределами видимой области

	// пытаемся отдать приказ пойти туда, куда тыкнули
	gameplay->Move(ptr, pos); 

}
void Player::TryToSelect(const RRMouse& mouseState) {
	Vector2 pos = TransofrmCoordinates(Vector2(mouseState.Position.X, mouseState.Position.Y), camera);
	selectedObject->Select(pos);
	 
	
	if (selectedObject->IsSmthSelected())
		if (IsActorVisible(pos)) {// если что-то выбрано и всё ок, то показываем контекстное меню
			contextMenus->ShowContextMenu();
		}
		else { // если объект выбран, но его не видно, то снимаем выделение
			selectedObject->SelectNothing();
		} 
}
     
bool Player::Finished() const {
	return finished && // была нажата кнопка завершения хода
		playerState == PlayerState::common && // закончились все анимации
		movingObjectsQueue->IsEmpty(); // все юниты закончили ходить
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
SelectedObject* Player::GetSelectedObject() {
	return selectedObject;
}
PlayerContextMenus* Player::GetContextMenus() {
	return contextMenus;
}
PlayerData* Player::GetPlayerData() {
	return playerData;
}
const Camera* Player::GetCamera() const {
	return camera;
}

void Player::Worker_Build(Worker* worker) {
	// если тип задачи не строительство, то произошла ошибка в вызове этого метода
	assert(worker->CurrentTask()->GetType() == TaskType::build);
	// подробности задачи
	auto task = static_cast<TaskBuild<BuildingType>*>(worker->CurrentTask());
	   
	// имеет ли игрок достаточно ресурсов для строительства  
	if (!playerData->Treasures()->Have(playerData->Researches()->GetPrice(task->GetObjectType()))) {
		worker->FailedTask(); // если не имеет, то задача не выполнима
		selectedObject->SelectNothing();
		return;
	}

	// строить можно в 4 соседних клетках, рядом с рабочим
	if (!selectPlace->InitializePlaces(worker->GetPosition())) {
		worker->FailedTask(); // если рядом нет свободных клеток, то задача невыполнима
		selectedObject->SelectNothing();
		return;
	}
	 
	// всё ок => переключаем состояние игрока на выбор места для строительства
	SwitchState(PlayerState::selectingPlace); 
} 

void Player::Worker_Become(Worker* worker) {
	// если тип задачи не специализация, то произошла ошибка в вызове этого метода
	assert(worker->CurrentTask()->GetType() == TaskType::build);

	// подробности задачи
	auto task = static_cast<TaskBuild<UnitType>*>(worker->CurrentTask());

	// пытаемся заплатить за специализацию
	if (playerData->Treasures()->Transaction(playerData->Researches()->GetPrice(task->GetObjectType()))) {
		// если ресурсов хватило, то создаём на месте рабочего новый юнит
		treasureFields->UpdateTreasureFields();
		ObjectsFactory::Instance()->MakeUnitAndReplace(worker, task->GetObjectType());
	}
	else { 
		worker->FailedTask(); // если не получилось, то сбрасываем задачу 
	}

	selectedObject->SelectNothing();
}
 
void Player::House_Produce(House* house) {
	// если тип задачи не начало производства, то произошла ошибка в вызове этого метода
	assert(house->CurrentTask()->GetType() == TaskType::produceStart); 
	 
	// подробности задачи
	auto task = static_cast<TaskProduceStart<Worker>*>(house->CurrentTask());

	if (playerData->Treasures()->Transaction(playerData->Researches()->GetPrice(UnitType::worker))) {
		// если ресурсов хватило, то меняем тип задачи на настоящее производство
		treasureFields->UpdateTreasureFields();
		house->SetTask(new TaskProduce<Worker>(task->GetValueToFinish()));
	}
	else {
		house->FailedTask();
	}

	selectedObject->SelectNothing();
}