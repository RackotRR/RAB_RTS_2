#include "SelectPlace.h"
#include "Pathfinder.h"
#include "GameIO.h"
#include "World.h"
#include "Objects.h"

SelectPlace::SelectPlace(Camera* camera, World* world)
	: camera(camera), 
	position(Vector2::WrongPosition),
	world(world)
{}

bool SelectPlace::InitializePlaces(const Vector2& center) { 
	// добавляем 4 соседние клетки:
	 
	const Level* level = world->GetLevel(); // уровень
	auto ground = GetGroundIn(center, 1, level->width, level->height); // 4 соседние клетки
	// проверяем
	for (auto& iter : ground) {
		ObjectType type = world->CheckPosition(iter); // смотрим тип актёра
		switch (type)
		{ 
		case ObjectType::ground: // если это ground
			if (level->ground[iter.Y][iter.X].GetType() != GroundType::water) // но не вода
				placesToSelect.insert(iter); // то добавляем эту клетку в набор
			break; 
		default:
			break;
		}
	}
	// возвращаем true, если есть хоть одна клетка в наборе
	return Selecting();
}

const Vector2& SelectPlace::GetPlace() const {
	return position;
}

bool SelectPlace::Selecting() const {
	return !placesToSelect.empty();
}

void SelectPlace::GenerateOutput() const {
	if (Selecting())
		for (auto& iter : placesToSelect) {
			Rectangle rect = {
					camera->GetDX() + iter.X * camera->GetCellSize(),
					camera->GetDY() + iter.Y * camera->GetCellSize(),
					camera->GetCellSize(),
					camera->GetCellSize() };
			GameIO::Instance()->DrawRectangle(rect, RRColor(50, 50, 250, 160));
		}
}

bool SelectPlace::ProcessInput(const RRMouse& mouseState) {
	if (!Selecting()) return false;
	Vector2 pos = TransofrmCoordinates(mouseState.Position, camera);
	for (auto& iter : placesToSelect) {
		if (pos == iter) {
			position = iter;
			return true;
		}
	}
	return false;
}

void SelectPlace::Shutdown() {
	placesToSelect.clear();
}