#pragma once
#include "RRMouse.h"
#include "KeyboardState.h"

class GameIO;

class Camera {
public:
	Camera();

	int GetDX() const;
	int GetDY() const;
	int GetCellSize() const;

	// �������� ��������� ������
	void Update();
private:
	// �������� �������� ������
	void UpdateOffset(const RRMouse& mouseState, const KeyboardState& keyState);
	// �������� ������ ������
	void UpdateScale(int newSize);

	// ���������� vx ��� ������� �� size
	double GetVX() const;
	// ���������� vy ��� ������� �� size
	double GetVY() const;

	double dx, dy, // �������� ������ �������� ���� ������ ������������ ������ (0, 0) 
		vx, vy; // �������� ��������

	int cellSize; // ������ ����� ������ (�������)

	GameIO* gameIO;
};