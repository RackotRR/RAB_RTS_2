#include "WorkerContextMenu.h"
#include <assert.h>
#include "Worker.h" 
#include "BuildingType.h"

WorkerContextMenu::WorkerContextMenu(int height, Worker* worker, Player* player) : 
	UnitContextMenu{ height, worker, player }, 
	worker{ worker }
{
	// ������ ����� ��������� ������ � ������, ���� ������� ������
	if (SeeingMaster()) {
		// ������ ������ ���� ������ � ���� �������, ���� ������ ������������ � WorkerTask
		AddButton(TextureType::factoryButton);
		AddButton(TextureType::houseButton);
		AddButton(TextureType::spaceportButton);
		AddButton(TextureType::tankButton);
		AddButton(TextureType::scoutButton);
	}
} 
 

void WorkerContextMenu::SendTask(uint8_t num) {
	/*
	����� ����� �������� ������ � ��������� ������, ����� ����� ���������� � �������� ���������
	*/
	switch (num)
	{ 
	case 0: // build factory
		worker->SetTask(new TaskBuild(BuildingType::factory));
		break;
	case 1: // build house
		worker->SetTask(new TaskBuild(BuildingType::house));
		break;
	case 2: // build spaceport
		worker->SetTask(new TaskBuild(BuildingType::spaceport));
		break;
	case 3: // become tank
		worker->SetTask(new TaskBuild(UnitType::tank));
		break;
	case 4: // become scout
		worker->SetTask(new TaskBuild(UnitType::scout));
		break;
	default:
		// ���� ���� �� ����� (��� ������ �������� ����� case)
		assert("ERROR in send task to worker by context menu" && false); 
	}
}