#pragma once
#include "RRMouse.h"
#include "KeyboardState.h"

class GameIO;

class Camera {
public:
	Camera();

	int GetDX() const;
	int GetDY() const;
	int GetCellSize() const;

	// обновить состо€ние камера
	void Update();
private:
	// обновить смещение камеры
	void UpdateOffset(const RRMouse& mouseState, const KeyboardState& keyState);
	// обновить мастаб камеры
	void UpdateScale(int newSize);

	// возвращает vx как функцию от size
	double GetVX() const;
	// возвращает vy как функцию от size
	double GetVY() const;

	double dx, dy, // смещение левого верхнего кра€ экрана относительно €чейки (0, 0) 
		vx, vy; // скорость смещени€

	int cellSize; // размер одной €чейки (масштаб)

	GameIO* gameIO;
};