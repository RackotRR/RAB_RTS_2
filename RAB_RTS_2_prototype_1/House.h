#pragma once
#include "Building.h"

class House : public Building {
public:
	House(const Vector2& position);

	// ���������� ��������� ������� ������ 
	void DoCurrentTask(TurnPhase phase = TurnPhase::common) override;
};
