#pragma once
#include "Task.h" 
#include "BuildingType.h"

template<typename T>
class TaskBuild : public Task {
public: 
	TaskBuild(T type) : TaskBuild(type, Vector2::WrongPosition) {}
	TaskBuild(T type, const Vector2& pos) : type{ type }, position{ pos } {
		SetType(TaskType::build);
	}

	void SetBuildType(T type) {
		this->type = type;
	}

	T GetObjectType() const {
		return type;
	}

	void SetPosition(const Vector2& pos) {
		position = pos;
	}

	const Vector2& GetPosition() const {
		return position;
	}
private:
	T type;
	Vector2 position;
};

class TaskBuildProduction : public TaskBuild<BuildingType> {
public:
	TaskBuildProduction(const TaskBuild<BuildingType>& taskBuild) :
		TaskBuild{ taskBuild }
	{
		SetType(TaskType::buildProduction);
	}

	TaskBuildProduction(BuildingType type, const Vector2& pos) : 
		TaskBuild{ type, pos }
	{
		SetType(TaskType::buildProduction);
	}
};