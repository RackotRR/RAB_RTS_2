#include "HasTask.h"
#include "Unit.h"
#include <assert.h>
#include <iostream>

HasTask::HasTask() : 
	taskNone{ new Task } 
{

}

HasTask::~HasTask() {
	ClearTasks();
}

Task* HasTask::CurrentTask() {
	size_t size = tasks.size();
	if (size == 0) return taskNone;

	return tasks[size - 1];
}

void HasTask::FinishCurrentTask() {
	assert(taskNone != CurrentTask());
	delete CurrentTask();
	tasks.pop_back();
}

void HasTask::FailedTask() {
	ClearTasks();
}
 
void HasTask::ClearTasks() {
	for (auto& iter : tasks) {
		delete iter;
	}
	tasks.clear();
}
 
void HasTask::AddTask(Task* task) {
	tasks.push_back(task);
}

void HasTask::SetTask(Task* task) {
	ClearTasks();
	tasks.push_back(task);
	// при установке задачи, актёр попытается выполнить её
	DoCurrentTask();
}

void HasTask::DoCurrentTask(TurnPhase phase) {
	switch (CurrentTask()->GetType())
	{ 
	case TaskType::none: 
		break;
	default:
		assert("Unknown task!" && false);
		break;
	}
}