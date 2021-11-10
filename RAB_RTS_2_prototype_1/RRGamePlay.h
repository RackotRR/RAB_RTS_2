#pragma once
#include "Vector2.h" 
#include "World.h"

/*
�����, ���������� �� ��������� �������� ����
*/
class RRGamePlay
{
public:
	RRGamePlay(World* world) : world(world) {}

	// ������� ��� ������� ���������
	bool Initialize();

	// ������� ��� ���������� ���������
	void Shutdown();

	// ��������� ���� ������������
	// ������ ���� �� ������� ����� �������� ��������� ������� ������
	// ����� ���� ��������� move points
	void ProductionPhase();
	  
	/// <summary>
	/// �������� ��������� ������� ���, ����� �� �������� � at 
	/// </summary>
	/// <param name="who">-��������� �� ���������� ������</param>
	/// <param name="at">-���� �� ��������</param>
	void Move(Unit* who, const Vector2& at);
	void MoveToAttack(Unit* who, const Vector2& at);
	void Attack(Unit* who, const Vector2& at);
	 
	   
	// ���������� ��������� �� ������ � ����
	World* GetWorld() {
		return world;
	}
private:   
	World* world;
};

