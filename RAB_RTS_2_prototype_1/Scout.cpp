#include "Scout.h"

Scout::Scout(const Vector2& position) : Unit(position) {
	SetType(UnitType::scout); 
}
// установить направление движения (для отрисовки)
void Scout::SetDirection(Direction direction)  {
	switch (direction)
	{
	case Direction::right: // право 
	case Direction::left: // лево
		HasUnitTexture::direction = direction;
		break;
	default:
		break;
	}
}
// получить угол поворота текстуры
double Scout::GetAngle() const  {
	return 0;
}
// отражение текстуры
DrawFlip Scout::GetDrawFlip() const  {
	switch (GetDirection())
	{
	case Direction::left:
		return DrawFlip::horizontal;
	case Direction::right:
	default:
		return DrawFlip::none;
	}
}