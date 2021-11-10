#pragma once

enum class TaskType {
	none,
	move,
	build,
	buildProduction,
	produce,
	produceStart
};

class Task
{
public:
	Task();
	virtual ~Task() {}
	TaskType GetType() const;
protected:
	void SetType(TaskType type);
private:
	TaskType type;
};


