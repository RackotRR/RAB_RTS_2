#pragma once
#include "Vector2.h"
#include "Direction.h"
class Unit;
class MoveAnimation
{
public:
	// ������������� �� �������� ��������
	bool IsMoving() const;

	// �������� �� � �� ����� ��������
	int GetMovingX() const;

	// �������� �� Y �� ����� ��������
	int GetMovingY() const;

	/// <summary>
	/// ������� ��� ������������ � ��������� ��������
	/// </summary> 
	void StartMoving(Direction dir); 


	/// <summary>
	/// ���������� �������� ������������. �������� ������ ���� 
	/// </summary>
	bool UpdateMovingAnimation();
protected:
	// ������� ����� ������ ��������������
	void InitializeMovingAnimation(Unit* unit);
private: 
	// ���������� vx ��� ������� �� size
	double GetVX() const;
	// ���������� vy ��� ������� �� size
	double GetVY() const;
	// ����� �� ��������� ��������
	void FinishMoving();

	Unit* unit;
	Direction direction;
	double movingX, movingY;
	int size;
	double vx = 8, vy = 8;

	// ���� true, �� ������� ���������� � ��������� ����
	// ���������� � ������ �������� � ����������� �����
	bool moving; 
};

