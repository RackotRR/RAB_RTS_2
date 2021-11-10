#pragma once
#include "World.h"

class SelectedObject {
public:
	SelectedObject(World* world);

	/// <summary>
	/// ������������� ���� selected, ���� ��� ������ ������.
	/// ���������� ���, ���� ������ �� ���� �������
	/// </summary>
	/// <param name="position"> - ���������� �������</param>
	/// <returns>���������� ��� �������, ������������ ���</returns>
	ObjectType Select(const Vector2& v);

	// ���������� ��������� ����� selected
	bool IsSmthSelected() const;

	// ���������� ����� �������
	void SelectNothing();

	// ���������� ���������� ���������� �������
	const Vector2& GetPosition() const;

	// ���������� ��� ���������� �������
	ObjectType GetType() const;
private:
	World* world;
	Vector2 position;
	ObjectType type;
	bool selected;
};