#pragma once
#include "Vector2.h" 
#include "World.h"

/*
Класс, отвечающий за симуляцию игрового мира
*/
class RRGamePlay
{
public:
	RRGamePlay(World* world) : world(world) {}

	// Вызвать для запуска симуляции
	bool Initialize();

	// Вызвать для завершения симуляции
	void Shutdown();

	// выполняет фазу производства
	// каждый юнит по очереди будет пытаться выполнить текущую задачу
	// после чего обновятся move points
	void ProductionPhase();
	  
	/// <summary>
	/// Изменить состояние объекта так, чтобы он двигался в at 
	/// </summary>
	/// <param name="who">-указатель на движущийся объект</param>
	/// <param name="at">-куда он движется</param>
	void Move(Unit* who, const Vector2& at);
	void MoveToAttack(Unit* who, const Vector2& at);
	void Attack(Unit* who, const Vector2& at);
	 
	   
	// Возвращает указатель на данные о мире
	World* GetWorld() {
		return world;
	}
private:   
	World* world;
};

