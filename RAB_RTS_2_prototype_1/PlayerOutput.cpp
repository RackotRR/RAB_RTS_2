#include "PlayerOutput.h"
#include "Player.h"   
#include "GameIO.h"
#include "RRGamePlay.h"
#include "World.h"
#include "Objects.h"
#include "SelectedObject.h"
#include "Camera.h"
 
 
void PlayerOutput::Initialize(Player* player, RRGamePlay* gameplay, int width, int height) {
	this->gameplay = gameplay;
	this->gameIO = GameIO::Instance();
	this->width = width;
	this->height = height; 
	this->player = player;
}

void PlayerOutput::DrawSelectedObject() {
	const Vector2& pos = player->GetSelectedObject()->GetPosition();
	auto camera = player->GetCamera();

	Rectangle rect = {
			camera->GetDX() + pos.X * camera->GetCellSize(),
			camera->GetDY() + pos.Y * camera->GetCellSize(),
			camera->GetCellSize(),
			camera->GetCellSize() };
	gameIO->DrawRectangle(rect, RRColor(50, 250, 50, 160));
}

void PlayerOutput::DrawWorld() {
	auto camera = player->GetCamera();
	const Level* level = gameplay->GetWorld()->GetLevel();

	const int size = camera->GetCellSize();
	const int dx = camera->GetDX();
	const int dy = camera->GetDY();
	
	DrawGround(level, dx, dy, size);
	DrawResources(level, dx, dy, size);
	DrawUnits(level, dx, dy, size);
	DrawBuildings(level, dx, dy, size);
}
 
void PlayerOutput::DrawUnits(const Level* level, int dx, int dy, int size) {
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

void PlayerOutput::DrawBuildings(const Level* level, int dx, int dy, int size) {
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

void PlayerOutput::DrawResources(const Level* level, int dx, int dy, int size) {
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

void PlayerOutput::DrawGround(const Level* level, int dx, int dy, int size) {
	// ground
	for (int j = 0; j < level->height; j++)
		for (int i = 0; i < level->width; i++) {
			if (!player->IsActorVisible(Vector2(i, j))) continue; // если объект не видно, то пропускаем его
			Rectangle rect = {
						dx + size * i,
						dy + size * j,
						size,
						size };
			switch (level->ground[j][i].GetType())
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
 