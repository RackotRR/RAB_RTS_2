#include "PlayerOutput.h"
#include "Player.h"   
#include "GameIO.h"
#include "RRGamePlay.h"
#include "World.h"
#include "Objects.h"
#include "SelectedObject.h"
#include "Camera.h"
 
 
PlayerOutput::PlayerOutput(Player* player, RRGamePlay* gameplay)
	:
	player{ player },
	gameIO{ GameIO::Instance() },
	gameplay{ gameplay },
	level{ gameplay->GetWorld()->GetLevel() },
	treasureFields{ player->GetPlayerData()->Treasures(), 64, 192 } // todo: заменить константы на проценты
{}

void PlayerOutput::DrawSelectedObject() {
	const Vector2& pos = player->GetSelectedObject().GetPosition();
	auto& camera = player->GetCamera();

	Rectangle rect = {
			camera.GetDX() + pos.X * camera.GetCellSize(),
			camera.GetDY() + pos.Y * camera.GetCellSize(),
			camera.GetCellSize(),
			camera.GetCellSize() };
	gameIO->DrawRectangle(rect, RRColor(50, 250, 50, 160));
}

void PlayerOutput::DrawWorld() {
	auto& camera = player->GetCamera(); 

	const int size = camera.GetCellSize();
	const int dx = camera.GetDX();
	const int dy = camera.GetDY();
	
	DrawGround(dx, dy, size);
	DrawResources(dx, dy, size);
	DrawUnits(dx, dy, size);
	DrawBuildings(dx, dy, size);
}
 
void PlayerOutput::DrawUnits(int dx, int dy, int size) {
	bool existMovedUnit = false;
	Vector2 keyMovedUnit; // данные для перемещение юнита
	Unit* who = nullptr;

	for (auto& iter : level->units) {
		if (!player->IsActorVisible(iter.second->GetPosition())) continue; // если объект не видно, то пропускаем его 
		if (iter.second->IsMoving()) { // если юнит движется
			keyMovedUnit = iter.second->GetPosition(); // сохраняем его ключ 
			if (iter.second->UpdateMovingAnimation()) { // обновляем его положение
				existMovedUnit = true; // говорим, что кто-то переместился
				who = iter.second;
			}
		}
		Rectangle rect = {
						dx + size * iter.second->GetPosition().X + iter.second->GetMovingX(),
						dy + size * iter.second->GetPosition().Y + iter.second->GetMovingY(),
						size,
						size };
		gameIO->DrawTexture(rect, iter.second->GetTexture(0), iter.second->GetAngle(), iter.second->GetDrawFlip());
	}

	// перемещение юнита
	if (existMovedUnit)  
		gameplay->GetWorld()->ReplaceUnit(keyMovedUnit, who); 
}

void PlayerOutput::DrawBuildings(int dx, int dy, int size) {
	// buildings
	for (auto& iter : level->buildings) {
		if (!player->IsActorVisible(iter.second->GetPosition())) continue; // если объект не видно, то пропускаем его
		Rectangle rect = {
						dx + size * iter.second->GetPosition().X,
						dy + size * iter.second->GetPosition().Y,
						size,
						size }; 
		gameIO->DrawTexture(rect, iter.second->GetTexture()); 
	}
}

void PlayerOutput::DrawResources(int dx, int dy, int size) {
	// resources
	for (auto& iter : level->resources) {
		if (!player->IsActorVisible(iter.second->GetPosition())) continue; // если объект не видно, то пропускаем его
		Rectangle rect = {
						dx + size * iter.second->GetPosition().X,
						dy + size * iter.second->GetPosition().Y,
						size,
						size };
		gameIO->DrawTexture(rect, iter.second->GetTexture(0));
	}
}

void PlayerOutput::DrawGround(int dx, int dy, int size) {  
	const auto& ground{ level->ground };

	// ground
	for (int j = 0; j < ground.SizeY(); j++)
		for (int i = 0; i < ground.SizeX(); i++) { 
			if (player->IsActorVisible(Vector2(i, j)) == false) 
				continue; // если объект не видно, то пропускаем его

			Rectangle rect{
				dx + size * i,
				dy + size * j,
				size,
				size
			};

			switch (ground(i, j).GetType())
			{
			case GroundType::grass:
				gameIO->DrawRectangle(rect, RRColor(0, 255, 0));
				break;
			case GroundType::rock:
				gameIO->DrawRectangle(rect, RRColor(50, 50, 50));
				break;
			case GroundType::sand:
				gameIO->DrawRectangle(rect, RRColor(255, 255, 0));
				break;
			case GroundType::water:
				gameIO->DrawRectangle(rect, RRColor(0, 0, 255));
				break;
			}
		}
}
 

void PlayerOutput::DrawTreasureFields() {
	treasureFields.UpdateTreasureFields();
	treasureFields.GenerateOutput();
}
 