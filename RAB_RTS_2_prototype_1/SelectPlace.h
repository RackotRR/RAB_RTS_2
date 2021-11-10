#pragma once
#include <unordered_set>
#include "Vector2.h"
#include "Camera.h"
#include "RRMouse.h"

class World;

class SelectPlace {
public: 
	SelectPlace(Camera* camera, World* world);

	// инициализируем набор клеток для выбора
	// возвращает false, если нет доступных клеток
	bool InitializePlaces(const Vector2& center);

	// получить координаты выбранной клетки
	const Vector2& GetPlace() const;

	// обновляет ввод. возвращает true, если была выбрана клетка
	bool ProcessInput(const RRMouse& mouseState);

	// вывести клетки на экран
	void GenerateOutput() const;

	// возвращает true, если есть из чего выбирать
	bool Selecting() const;

	void Shutdown();
private:
	World* world;
	Camera* camera; 
	Vector2 position;
	std::unordered_set<Vector2, HashVector2> placesToSelect;
};