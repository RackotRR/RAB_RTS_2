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
	common, // ����� ����� (�� ���������)
	moveAnimation, // �������� ������������. ��������� ����� �������� ����� ����������� � �������
	selectingPlace, // ����� ����� (��� �������������). ��������� ����� ��������, ����� ������ ����� � ������ (�������������)
	productionPhase // ���� ������������ (��� �������� �������, ����������� background tasks)
};


/*
UI. ��������� ��, ��� ����� ����� � ������ �� ������
� ������� ������ ���� - ��������� � ���������� ������� RRGamePlay.
��������� ���� ������ � ������� ��������
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

	// ��������� ��������(treasure) ������ � ��������� ������� � ���
	PlayerData* playerData{};
	PlayerOutput playerOutput;

	// ��������� ������
	PlayerState playerState{ PlayerState::common };

public:
	Player(RRGamePlay* gameplay, PlayerData* playerData);
	Player(Player&&) = default;
	Player& operator=(Player&&) = default; 

	// ������ ����� ���
	void StartTurn();
	// �������� ��� � ��������� ��� �������� ����������
	bool Finished() const;

	// ��������� �����
	void ProcessInput(const RRMouse& mouseState, const KeyboardState& keyState);
	void Update();
	void GenerateOutput(); 
	   
	void SwitchState(PlayerState state);
	PlayerState GetPlayerState() const;
	 
	RRGamePlay* GetRRGamePlay();
	const SelectedObject& GetSelectedObject(); 
	PlayerData* GetPlayerData();
	const Camera& GetCamera() const;

	// ����� �� ������ �� �����������
	// ��������� ���������� ����� ��������� ����!
	bool IsActorVisible(const Vector2& pos) const;  

	// ���������� ��������� ������
	// � worker ������� ������� ������ ���� ������ �������������
	void Worker_Build(Worker* worker);
	void Worker_Become(Worker* worker); 

	void House_Produce(House* house);
private: 
	// ��������� ���
	void FinishTurn();

	// ������� ����������
	void UpdateCommonState(const RRMouse& mouseState, const KeyboardState& keyState);
	void TryToSelect(const RRMouse& mouseState);
	void TryToMove(const RRMouse& mouseState); 
	  
	void UpdateSelectingPlace(const RRMouse& mouseState);
	// ��������� �������� ����� ���������� ���� 
	// �� �������� ���������� ���������� ������
	void UpdateFinishingTurn(); 
	 

	Player(Player&) = delete;
	auto operator=(Player&) = delete;
};

