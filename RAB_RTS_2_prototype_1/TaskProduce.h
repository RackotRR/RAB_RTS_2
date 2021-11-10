#pragma once
#include "Task.h"  

template<typename T>
class TaskProduce : public Task {
public:
	TaskProduce(unsigned short valueToFinish) :
		valueToFinish{ valueToFinish },
		currentValue{}
	{ 
		SetType(TaskType::produce);
	}

	int GetValueToProduce() const {
		return valueToFinish - currentValue;
	}

	bool Produce(unsigned short value) {
		currentValue += value;
		return currentValue >= valueToFinish;
	}

	unsigned short GetValueToFinish() const {
		return valueToFinish;
	}
	unsigned short GetCurrentValue() const {
		return currentValue;
	}
private:
	unsigned short currentValue;
	const unsigned short valueToFinish;
};

template<typename T>
class TaskProduceStart : public Task {
public:
	TaskProduceStart(unsigned short valueToFinish) :
		valueToFinish{ valueToFinish }
	{
		SetType(TaskType::produceStart);
	}
	unsigned short GetValueToFinish() const {
		return valueToFinish;
	}
private:
	const unsigned short valueToFinish;
};