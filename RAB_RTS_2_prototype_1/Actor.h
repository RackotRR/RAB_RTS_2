#pragma once
#include "Vector2.h" 
#include <unordered_map>
using std::unordered_map;

/*
Базовый класс для всех сущностей в игре
Сущности идентифицируются координатами (position)
В один момент по одинаковым координатам не может находиться два объекта одного типа 
*/
class Actor
{
public:
	Actor(const Vector2& position) : position(position) {}
	virtual ~Actor() {}
  
	// по умолчанию координата - const
	const Vector2& GetPosition() const {
		return position;
	}
	void SetPosition(const Vector2& position) {
		this->position = position;
	}
protected: 
	Vector2 position; 
};

