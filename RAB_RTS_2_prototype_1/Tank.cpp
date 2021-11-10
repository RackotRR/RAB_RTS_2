#include "Tank.h"

Tank::Tank(const Vector2& position) : Unit(position) {
	SetType(UnitType::tank); 
}

// ���������� ����������� �������� (��� ���������)
void Tank::SetDirection(Direction direction) {
	HasUnitTexture::direction = direction;
}
// �������� ���� �������� ��������
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
// ��������� ��������
DrawFlip Tank::GetDrawFlip() const {
	return DrawFlip::none;
}