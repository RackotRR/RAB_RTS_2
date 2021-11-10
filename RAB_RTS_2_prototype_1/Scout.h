#pragma once
#include "Unit.h"

class Scout : public Unit {
public:
	Scout(const Vector2& position);
	// установить направление движения (для отрисовки)
	void SetDirection(Direction direction) override;
	// получить угол поворота текстуры
	double GetAngle() const override;
	// отражение текстуры
	DrawFlip GetDrawFlip() const override;
	 
};