#pragma once
#include "Vector2.h"
#include "Direction.h"
class Unit;
class MoveAnimation
{
public:
	// проигрывается ли анимация движения
	bool IsMoving() const;

	// смещение по Х во время движения
	int GetMovingX() const;

	// смещение по Y во время движения
	int GetMovingY() const;

	/// <summary>
	/// вызвать для переключения в состояние движения
	/// </summary> 
	void StartMoving(Direction dir); 


	/// <summary>
	/// обновление анимации передвижения. вызывать каждый кадр 
	/// </summary>
	bool UpdateMovingAnimation();
protected:
	// вызвать перед первым использованием
	void InitializeMovingAnimation(Unit* unit);
private: 
	// возвращает vx как функцию от size
	double GetVX() const;
	// возвращает vy как функцию от size
	double GetVY() const;
	// выйти из состояния движения
	void FinishMoving();

	Unit* unit;
	Direction direction;
	double movingX, movingY;
	int size;
	double vx = 8, vy = 8;

	// если true, то лочится управление и двигается юнит
	// включается в начале движения и выключается после
	bool moving; 
};

