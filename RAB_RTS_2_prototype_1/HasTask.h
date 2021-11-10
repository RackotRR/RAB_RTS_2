#pragma once
#include <vector>
#include "Task.h"
#include <assert.h>

enum class TurnPhase {
	common,
	production
};

class HasTask
{
public:
	HasTask();
	~HasTask();

	Task* CurrentTask();
	void FinishCurrentTask();
	void FailedTask();

	// Если текущая (верхняя) задача невыполнима, то невыполнимы оказываются все. Поэтому все будут удалены
	void ClearTasks();

	/*
	сложные задачи добавляются, начиная с последней части.
	например, добавляется задача "Атака". "Атака" добавляет задачу "Идти".
	Если текущая (верхняя) задача невыполнима, то невыполнимы оказываются все. Поэтому все будут удалены
	*/
	void AddTask(Task* task);

	void SetTask(Task* task);
	virtual void DoCurrentTask(TurnPhase phase = TurnPhase::common);
private:
	Task* taskNone;
	std::vector<Task*> tasks;
};

