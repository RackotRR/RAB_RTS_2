#pragma once
#include <unordered_set>
#include "Vector2.h"
#include "Camera.h"
#include "RRMouse.h"

class World;

class SelectPlace {
public: 
	SelectPlace(Camera* camera, World* world);

	// �������������� ����� ������ ��� ������
	// ���������� false, ���� ��� ��������� ������
	bool InitializePlaces(const Vector2& center);

	// �������� ���������� ��������� ������
	const Vector2& GetPlace() const;

	// ��������� ����. ���������� true, ���� ���� ������� ������
	bool ProcessInput(const RRMouse& mouseState);

	// ������� ������ �� �����
	void GenerateOutput() const;

	// ���������� true, ���� ���� �� ���� ��������
	bool Selecting() const;

	void Shutdown();
private:
	World* world;
	Camera* camera; 
	Vector2 position;
	std::unordered_set<Vector2, HashVector2> placesToSelect;
};