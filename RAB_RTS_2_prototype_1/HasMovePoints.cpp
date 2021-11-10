#include "HasMovePoints.h"

HasMovePoints::HasMovePoints() : movePoints(), maxMovePoints() {}

int HasMovePoints::GetMovePoints() const {
	return movePoints;
}

int HasMovePoints::GetMaxMovePoints() const {
	return maxMovePoints;
}

void HasMovePoints::SetMaxMovePoints(int val) {
	assert(val >= 0);
	maxMovePoints = val;
}

void HasMovePoints::SetMovePoints(int val) {
	assert(val >= 0);
	movePoints = val;
}

void HasMovePoints::ResetMovePoints() {
	movePoints = maxMovePoints;
}

// вернёт false, если очки передвижени закончатся
bool HasMovePoints::TryToSpendMovePoints(int val) {
	if (movePoints - val < 0)
		return false;
	else {
		movePoints -= val;
		return true;
	}
}