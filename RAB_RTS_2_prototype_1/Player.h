#pragma once 
#include "Vector2.h"
#include <set>
#include <unordered_map> 
#include <unordered_set>
#include <vector>
class RRGamePlay;
class World;
class PlayerOutput;
class Unit;
class Worker;
class House;
class ContextMenu;
class PlayerData;
class ContentField;
struct RRMouse;
class KeyboardState;
class GameIO;
class SelectedObject;
class TreasureFields;
class PlayerContextMenus;
class MovingObjectsQueue;
class Camera;
class SelectPlace;


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
public:
	Player();

	bool Initialize(RRGamePlay* gameplay, PlayerData* playerData);
	void Shutdown();

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
	SelectedObject* GetSelectedObject();
	PlayerContextMenus* GetContextMenus();
	PlayerData* GetPlayerData();
	const Camera* GetCamera() const;

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

	 
	bool finished = false; 
	 
	GameIO* gameIO;  
	RRGamePlay* gameplay;
	World* world;
	PlayerOutput* playerOut;

	SelectedObject* selectedObject;
	SelectPlace* selectPlace;
	TreasureFields* treasureFields;
	PlayerContextMenus* contextMenus;
	MovingObjectsQueue* movingObjectsQueue;
	Camera* camera;
	
	 
	int width, height;
	  
	// хранилище ресурсов(treasure) игрока и интерфейс доступа к ним
	PlayerData* playerData;  
	 
	// состояние игрока
	PlayerState playerState; 
};

