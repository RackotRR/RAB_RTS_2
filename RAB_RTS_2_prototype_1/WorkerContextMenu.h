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
	// отправить задачу юниту
	void SendTask(uint8_t num) override; 
 
	Worker* worker;
}; 