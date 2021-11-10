#pragma once
#include "Vector2.h"
#include "Actor.h"
#include <limits>
/*
Тип поверхности. Используется как проверка типа поверхности во время выполнения
*/
enum class GroundType {
	none,
	grass,
	sand,
	rock,
	water
};

/*
Клетка на поле. Характеризуется типом. Хранится в виде двумерного массива, координаты берутся оттуда
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

