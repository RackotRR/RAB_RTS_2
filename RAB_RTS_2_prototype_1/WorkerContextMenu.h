#pragma once
#include "UnitContextMenu.h"
#include <vector>
#include "Circle.h"

class Worker; 

class WorkerContextMenu : public UnitContextMenu
{
public:
	WorkerContextMenu(int height, Worker* worker, Player* player); 

private:  
	// ��������� ������ �����
	void SendTask(uint8_t num) override; 
 
	Worker* worker;
}; 