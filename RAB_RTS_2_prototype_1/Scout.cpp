#include "Scout.h"

Scout::Scout(const Vector2& position) : Unit(position) {
	SetType(UnitType::scout); 
}
// ���������� ����������� �������� (��� ���������)
void Scout::SetDirection(Direction direction)  {
	switch (direction)
	{
	case Direction::right: // ����� 
	case Direction::left: // ����
		HasUnitTexture::direction = direction;
		break;
	default:
		break;
	}
}
// �������� ���� �������� ��������
double Scout::GetAngle() const  {
	return 0;
}
// ��������� ��������
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