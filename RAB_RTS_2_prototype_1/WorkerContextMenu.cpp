#include "WorkerContextMenu.h"
#include <assert.h>
#include "Worker.h" 
#include "BuildingType.h"

WorkerContextMenu::WorkerContextMenu(int height, Worker* worker, Player* player) : 
	UnitContextMenu{ height, worker, player }, 
	worker{ worker }
{
	// кнопки будут добавлены только в случае, если смотрит хозяит
	if (SeeingMaster()) {
		// кнопки должны быть именно в этом порядке, либо менять одновременно с WorkerTask
		AddButton(TextureType::factoryButton);
		AddButton(TextureType::houseButton);
		AddButton(TextureType::spaceportButton);
		AddButton(TextureType::tankButton);
		AddButton(TextureType::scoutButton);
	}
} 
 

void WorkerContextMenu::SendTask(uint8_t num) {
	/*
	когда будет закончен модуль с ресурсами игрока, можно будет приступать к отправке сообщений
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
		// быть того не может (или забыли добавить новый case)
		assert("ERROR in send task to worker by context menu" && false); 
	}
}