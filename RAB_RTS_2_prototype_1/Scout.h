#pragma once
#include "Unit.h"

class Scout : public Unit {
public:
	Scout(const Vector2& position);
	// ���������� ����������� �������� (��� ���������)
	void SetDirection(Direction direction) override;
	// �������� ���� �������� ��������
	double GetAngle() const override;
	// ��������� ��������
	DrawFlip GetDrawFlip() const override;
	 
};