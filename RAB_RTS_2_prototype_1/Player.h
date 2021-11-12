#pragma once 
//#include <set>
//#include <unordered_map> 
//#include <unordered_set>
//#include <vector>
#include <memory>

#include "Vector2.h"
#include "Camera.h"
#include "PlayerOutput.h"
#include "SelectedObject.h"

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
class TreasureFields;
class PlayerContextMenus;
class MovingObjectsQueue; 
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
	Player(RRGamePlay* gameplay, PlayerData* playerData);
	Player(Player&&) = default;
	Player& operator=(Player&&) = default;
	~Player();

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
	PlayerContextMenus* GetContextMenus();
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

	 
	bool finished{ false };
	 
	GameIO* gameIO{};
	RRGamePlay* gameplay{};
	World* world{};
	PlayerOutput playerOutput;

	SelectedObject selectedObject;
	SelectPlace* selectPlace{};
	TreasureFields* treasureFields{};
	PlayerContextMenus* contextMenus{};
	MovingObjectsQueue* movingObjectsQueue{};
	Camera camera;
	 
	size_t width, height;
	  
	// ��������� ��������(treasure) ������ � ��������� ������� � ���
	PlayerData* playerData{};
	 
	// ��������� ������
	PlayerState playerState{ PlayerState::common };

	Player(Player&) = delete;
	auto operator=(Player&) = delete;
};

