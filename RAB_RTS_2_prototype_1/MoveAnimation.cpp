#include "MoveAnimation.h"
#include "Unit.h"
#include "GameIO.h"
#include "Player.h"
#include "Camera.h"
 
bool MoveAnimation::IsMoving() const {
	return moving;
}
 
int MoveAnimation::GetMovingX() const {
	return static_cast<int>(movingX);
}
 
int MoveAnimation::GetMovingY() const {
	return static_cast<int>(movingY);
}

void MoveAnimation::StartMoving(Direction dir) {
	direction = dir;
	moving = true; 
	unit->GetMaster()->SwitchState(PlayerState::moveAnimation);
}

void MoveAnimation::InitializeMovingAnimation(Unit* unit) {
	this->unit = unit;
	movingX = 0;
	movingY = 0;
	moving = false;
}

bool MoveAnimation::UpdateMovingAnimation() {
	this->size = unit->GetMaster()->GetCamera().GetCellSize();

	switch (direction)
	{
	case Direction::up:
		movingY -= GetVY();
		if (abs(movingY) >= size) {
			unit->SetPosition(unit->GetPosition() + Vector2(0, -1));
			FinishMoving(); // закончить движение
			unit->Move(false); // если надо, то возобновить  
			return true;
		}
		break;
	case Direction::right:
		movingX += GetVX();
		if (abs(movingX) >= size) {
			unit->SetPosition(unit->GetPosition() + Vector2(1, 0));
			FinishMoving();
			unit->Move(false);
			return true;
		}
		break;
	case Direction::down:
		movingY += GetVY();
		if (abs(movingY) >= size) {
			unit->SetPosition(unit->GetPosition() + Vector2(0, 1));
			FinishMoving();
			unit->Move(false);
			return true;
		}
		break;
	case Direction::left:
		movingX -= GetVX();
		if (abs(movingX) >= size) {
			unit->SetPosition(unit->GetPosition() + Vector2(-1, 0));
			FinishMoving();
			unit->Move(false);
			return true;
		}
		break; 
	} 
	return false;
}
 
void MoveAnimation::FinishMoving() {
	movingX = 0;
	movingY = 0;
	moving = false;
	unit->GetMaster()->SwitchState(PlayerState::common);
}

double  MoveAnimation::GetVX() const {
	return vx * size * GameIO::Instance()->GetTicks();
}
// возвращает vy как функцию от size
double  MoveAnimation::GetVY() const {
	return vy * size * GameIO::Instance()->GetTicks();
}