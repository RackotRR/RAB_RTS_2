#include "HouseContextMenu.h"
#include "ProgressBar.h"
#include "House.h"
#include "TaskProduce.h"
#include "Player.h"
#include "PlayerData.h"
class Worker;

HouseContextMenu::HouseContextMenu(int height, House* house, Player* player) :
	BuildingContextMenu{ height, house, player },
	house{ house }
{
	if (SeeingMaster()) {
		if (house->CurrentTask()->GetType() != TaskType::produce) {
			AddButton(TextureType::manButton);
		}
		else if (house->GetOwner() == 1) {
			TextureType type[5];
			type[0] = TextureType::manButton1_1;
			type[1] = TextureType::manButton1_2;
			type[2] = TextureType::manButton1_3;
			type[3] = TextureType::manButton1_4;
			type[4] = TextureType::manButton;
			auto taskProduce = static_cast<TaskProduce<Worker>*>(house->CurrentTask());
			AddButton(ProgressBar::GetTexture<5>(taskProduce->GetCurrentValue(), taskProduce->GetValueToFinish(), type));
		}
		else if (house->GetOwner() == 2) {
			TextureType type[5];
			type[0] = TextureType::manButton;
			type[1] = TextureType::manButton2_1;
			type[2] = TextureType::manButton2_2;
			type[3] = TextureType::manButton2_3;
			type[4] = TextureType::manButton2_4;
			auto taskProduce = static_cast<TaskProduce<Worker>*>(house->CurrentTask());
			AddButton(ProgressBar::GetTexture<5>(taskProduce->GetCurrentValue(), taskProduce->GetValueToFinish(), type));
		}
	}
}
 

void HouseContextMenu::SendTask(uint8_t num) {
	switch (num)
	{
	case 0:
		house->SetTask(new TaskProduceStart<Worker>(house->GetMaster()->GetPlayerData()->Researches()->GetPointsToProduceUnit(UnitType::worker)));
		break;
	default:
		// быть того не может (или забыли добавить новый case)
		assert("ERROR in send task to worker by context menu" && false);
		break;
	}
}