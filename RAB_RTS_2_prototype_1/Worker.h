#pragma once
#include "Unit.h"
#include "TaskBuild.h" 
  
class Worker : public Unit {
public:
	Worker(const Vector2& position);

	// установить направление движения (для отрисовки)
	void SetDirection(Direction direction) override;

	// получить угол поворота текстуры
	double GetAngle() const override;

	// отражение текстуры
	DrawFlip GetDrawFlip() const override;

	// попытаться выполнить текущую задачу
	void DoCurrentTask(TurnPhase phase = TurnPhase::common) override;
	
private:
	void SpendMovePointsOnBuilding();
};