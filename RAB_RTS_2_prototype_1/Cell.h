#pragma once
#include "Vector2.h"
#include "Actor.h"
#include <limits>
/*
��� �����������. ������������ ��� �������� ���� ����������� �� ����� ����������
*/
enum class GroundType {
	none,
	grass,
	sand,
	rock,
	water
};

/*
������ �� ����. ��������������� �����. �������� � ���� ���������� �������, ���������� ������� ������
*/
class Cell  
{ 
public:
	Cell() : type(GroundType::none) {}
	void SetType(GroundType type) {  
		this->type = type;  
	} 
	GroundType GetType() const { return type; }  
private:  
	GroundType type;
};

