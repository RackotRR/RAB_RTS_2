#pragma once
#include "World.h"

class SelectedObject {
public:
	SelectedObject(World* world);

	/// <summary>
	/// Устанавливает флаг selected, если был выбран объект.
	/// Сбрасывает его, если ничего не было выбрано
	/// </summary>
	/// <param name="position"> - координата объекта</param>
	/// <returns>Возвращает тип объекта, находящегося там</returns>
	ObjectType Select(const Vector2& v);

	// Возвращает состояние флага selected
	bool IsSmthSelected() const;

	// Сбрасывает выбор объекта
	void SelectNothing();

	// возвращает координаты выбранного объекта
	const Vector2& GetPosition() const;

	// Возвращает тип выбранного объекта
	ObjectType GetType() const;
private:
	World* world;
	Vector2 position;
	ObjectType type;
	bool selected;
};