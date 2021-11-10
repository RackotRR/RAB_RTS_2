#pragma once
#include "Vector2.h"
#include "Actor.h"
#include "HasTexture.h"
#include "ResourceType.h"

/*
	�����, ���������� �� ������� �� �����
*/
class Resource : public Actor, public HasTexture
{
public: 
	/*
	��� ��������� �������, ������� ��� �������� ��������������� ��� ��������
	*/
	Resource(const Vector2& position, int value, int maxValue, ResourceType type);
  
	ResourceType GetType() const;

	// ������ val ������ �������. ���������� ���-�� ����������� �������
	int Take(int val);

	// ���������� �� ������. ���� ��, �� ��� ������� �������
	bool IsOver() const;

	int GetValue() const;
	int GetMaxValue() const;
private:
	ResourceType type;
	int value;
	int maxValue;
};
 