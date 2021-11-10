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
public:
	Player();

	bool Initialize(RRGamePlay* gameplay, PlayerData* playerData);
	void Shutdown();

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
	SelectedObject* GetSelectedObject();
	PlayerContextMenus* GetContextMenus();
	PlayerData* GetPlayerData();
	const Camera* GetCamera() const;

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
	  
	// ��������� ��������(treasure) ������ � ��������� ������� � ���
	PlayerData* playerData;  
	 
	// ��������� ������
	PlayerState playerState; 
};

