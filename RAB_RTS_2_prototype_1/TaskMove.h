#pragma once
#include "Task.h" 
#include "Vector2.h"

class TaskMove : public Task
{
public:
	TaskMove() : Task(), goal() {
		SetType(TaskType::move);
	}
	TaskMove(const Vector2& v) : Task(), goal(v) {
		SetType(TaskType::move);
	}
	void SetGoal(const Vector2& goal);
	Vector2 GetGoal() const;
private:
	Vector2 goal;
};