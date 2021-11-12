#pragma once
#include "Vector2.h"
#include "RRMouse.h"

class ContextMenu; 
class World;
class SelectedObject;
class Player;

class PlayerContextMenus {
public:
	PlayerContextMenus(const SelectedObject& selectedObject, World* world, Player* player);
	~PlayerContextMenus();

	// ��������� �����
	bool ProcessInput(const RRMouse& mouseState);

	// ���������� ���������
	void Update();

	// ����� �� �����
	void GenerateOutput();

	// �������� ����������� ���� ��� ���������� �������
	void ShowContextMenu();
private:
	std::unordered_map<Vector2, ContextMenu*, HashVector2> contextMenus;
	World* world;
	const SelectedObject& selectedObject;
	Player* player;
};
 