#include "SelectPlace.h"
#include "Pathfinder.h"
#include "GameIO.h"
#include "World.h"
#include "Objects.h"

SelectPlace::SelectPlace(const Camera& camera, World* world)
	: 
	camera{ camera },
	position{ Vector2::WrongPosition },
	world{ world }
{}

void SelectPlace::InitializePlaces(const Vector2& center) { 
	// добавляем 4 соседние клетки:
	 
	const Level* level = world->GetLevel(); // уровень
	auto ground = GetGroundIn(center, 1, level->size); // 4 соседние клетки
	// проверяем
	for (auto& cell : ground) {
		ObjectType type = world->CheckPosition(cell); // смотрим тип актёра
		switch (type)
		{ 
		case ObjectType::ground: // если это ground
			if (level->ground(cell.X, cell.Y).GetType() != GroundType::water) // но не вода
				placesToSelect.insert(cell); // то добавляем эту клетку в набор
			break; 
		default:
			break;
		}
	} 
}

const Vector2& SelectPlace::GetPlace() const {
	return position;
}

bool SelectPlace::IsEmpty() const {
	return placesToSelect.empty();
}

void SelectPlace::GenerateOutput() const {
	if (!IsEmpty())
		for (auto& iter : placesToSelect) {
			Rectangle rect = {
					camera.GetDX() + iter.X * camera.GetCellSize(),
					camera.GetDY() + iter.Y * camera.GetCellSize(),
					camera.GetCellSize(),
					camera.GetCellSize() };
			GameIO::Instance()->DrawRectangle(rect, RRColor(50, 50, 250, 160));
		}
}

bool SelectPlace::ProcessInput(const RRMouse& mouseState) {
	if (IsEmpty()) 
		return false;

	Vector2 pos = TransofrmCoordinates(mouseState.Position, camera);
	for (auto& iter : placesToSelect) {
		if (pos == iter) {
			position = iter;
			return true;
		}
	}
	return false;
}

void SelectPlace::ClearPlacesToSelect() {
	placesToSelect.clear();
}