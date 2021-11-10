#pragma once
#include "Vector2.h"
#include "Actor.h"
#include "HasTexture.h"
#include "ResourceType.h"

/*
	 ласс, отвечающий за ресурсы на карте
*/
class Resource : public Actor, public HasTexture
{
public: 
	/*
	Ќет наследных классов, поэтому все значени€ устанавливаютс€ при создании
	*/
	Resource(const Vector2& position, int value, int maxValue, ResourceType type);
  
	ResourceType GetType() const;

	// ƒобыть val единиц ресурса. ¬озвращает кол-во полученного ресурса
	int Take(int val);

	// закончилс€ ли ресурс. если да, то его следует удалить
	bool IsOver() const;

	int GetValue() const;
	int GetMaxValue() const;
private:
	ResourceType type;
	int value;
	int maxValue;
};
 