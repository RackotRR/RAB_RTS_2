#pragma once
#include "Vector2.h" 
#include <unordered_map>
using std::unordered_map;

/*
������� ����� ��� ���� ��������� � ����
�������� ���������������� ������������ (position)
� ���� ������ �� ���������� ����������� �� ����� ���������� ��� ������� ������ ���� 
*/
class Actor
{
public:
	Actor(const Vector2& position) : position(position) {}
	virtual ~Actor() {}
  
	// �� ��������� ���������� - const
	const Vector2& GetPosition() const {
		return position;
	}
	void SetPosition(const Vector2& position) {
		this->position = position;
	}
protected: 
	Vector2 position; 
};

