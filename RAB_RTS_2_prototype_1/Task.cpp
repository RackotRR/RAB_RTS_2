#include "Task.h"
#include "TaskMove.h"
#include "TaskBuild.h" 
////////////////////////////////////////////////////////////
/*
	Task
*/

Task::Task() : type(TaskType::none) {}

TaskType Task::GetType() const {
	return type;
}

void Task::SetType(TaskType type) {
	this->type = type;
}


///////////////////////////////////////////////////////////
/*
	TaskMove
*/

void TaskMove::SetGoal(const Vector2& goal) {
	this->goal = goal;
}

Vector2 TaskMove::GetGoal() const {
	return goal;
}
 