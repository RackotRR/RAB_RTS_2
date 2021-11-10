#pragma once
#include "Unit.h"

class Tank : public Unit {
public:
	Tank(const Vector2& position);

	// ���������� ����������� �������� (��� ���������)
	void SetDirection(Direction direction) override;
	// �������� ���� �������� ��������
	double GetAngle() const override;
	// ��������� ��������
	DrawFlip GetDrawFlip() const override;

};