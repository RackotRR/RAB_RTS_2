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

	// ���� ������� (�������) ������ �����������, �� ����������� ����������� ���. ������� ��� ����� �������
	void ClearTasks();

	/*
	������� ������ �����������, ������� � ��������� �����.
	��������, ����������� ������ "�����". "�����" ��������� ������ "����".
	���� ������� (�������) ������ �����������, �� ����������� ����������� ���. ������� ��� ����� �������
	*/
	void AddTask(Task* task);

	void SetTask(Task* task);
	virtual void DoCurrentTask(TurnPhase phase = TurnPhase::common);
private:
	Task* taskNone;
	std::vector<Task*> tasks;
};

