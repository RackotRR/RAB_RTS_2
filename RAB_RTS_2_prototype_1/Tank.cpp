#include "Tank.h"

Tank::Tank(const Vector2& position) : Unit(position) {
	SetType(UnitType::tank); 
}

// установить направление движения (для отрисовки)
void Tank::SetDirection(Direction direction) {
	HasUnitTexture::direction = direction;
}
// получить угол поворота текстуры
double Tank::GetAngle() const {
	switch (GetDirection())
	{
	case Direction::left:
		return 270;
	case Direction::down:
		return 180;
	case Direction::right:
		return 90;
	case Direction::up:
	default:
		return 0;
	}
}
// отражение текстуры
DrawFlip Tank::GetDrawFlip() const {
	return DrawFlip::none;
}