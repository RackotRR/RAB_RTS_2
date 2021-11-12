#pragma once   
#include "Vector2.h"
#include "Camera.h"
#include "PlayerOutput.h"
#include "SelectedObject.h"
#include "SelectPlace.h"
#include "MovingObjectsQueue.h"
#include "PlayerContextMenus.h"

class RRGamePlay;
class World; 
class Unit;
class Worker;
class House;
class ContextMenu;
class PlayerData;
class ContentField;
struct RRMouse;
class KeyboardState;
class GameIO;   


enum class PlayerState {
	common, // общий режим (по умолчанию)
	moveAnimation, // анимация передвижения. запрещены любые действия кроме манипуляций с камерой
	selectingPlace, // выбор места (для строительства). запрещены любые действия, кроме выбора места и отмены (строительства)
	productionPhase // фаза производства (нет контроля игроком, выполняются background tasks)
};


/*
UI. Переводит то, что игрок видит и тыкает на экране
в команды внутри игры - формирует и отправляет команды RRGamePlay.
Переводит ввод игрока в термины геймплея
*/ 
class Player
{
	bool finished{ false };

	GameIO* gameIO{};
	RRGamePlay* gameplay{};
	World* world{};

	SelectedObject selectedObject;
	SelectPlace selectPlace;
	PlayerContextMenus contextMenus;
	MovingObjectsQueue movingObjectsQueue;
	Camera camera;

	// хранилище ресурсов(treasure) игрока и интерфейс доступа к ним
	PlayerData* playerData{};
	PlayerOutput playerOutput;

	// состояние игрока
	PlayerState playerState{ PlayerState::common };

public:
	Player(RRGamePlay* gameplay, PlayerData* playerData);
	Player(Player&&) = default;
	Player& operator=(Player&&) = default; 

	// начать новый ход
	void StartTurn();
	// закончил ход и завершены все анимации завершения
	bool Finished() const;

	// обработка ввода
	void ProcessInput(const RRMouse& mouseState, const KeyboardState& keyState);
	void Update();
	void GenerateOutput(); 
	   
	void SwitchState(PlayerState state);
	PlayerState GetPlayerState() const;
	 
	RRGamePlay* GetRRGamePlay();
	const SelectedObject& GetSelectedObject(); 
	PlayerData* GetPlayerData();
	const Camera& GetCamera() const;

	// виден ли объект по координатам
	// проверять координаты перед передачей сюда!
	bool IsActorVisible(const Vector2& pos) const;  

	// попытаться построить здание
	// у worker текущей задачей должна быть задача строительства
	void Worker_Build(Worker* worker);
	void Worker_Become(Worker* worker); 

	void House_Produce(House* house);
private: 
	// закончить ход
	void FinishTurn();

	// обычное управление
	void UpdateCommonState(const RRMouse& mouseState, const KeyboardState& keyState);
	void TryToSelect(const RRMouse& mouseState);
	void TryToMove(const RRMouse& mouseState); 
	  
	void UpdateSelectingPlace(const RRMouse& mouseState);
	// выполняет действия после завершения хода 
	// до передачи управления следующему игроку
	void UpdateFinishingTurn(); 
	 

	Player(Player&) = delete;
	auto operator=(Player&) = delete;
};

