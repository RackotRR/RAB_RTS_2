#include "RRGamePlay.h" 
#include "TaskMove.h"
#include "Objects.h"
#include "Pathfinder.h"

bool RRGamePlay::Initialize() {
	if (!world) return false;
	world->UpdateChangedCoordinates();
	return true;
}

void RRGamePlay::Shutdown() {
	// *world - этот объект будет удалён в GameEngine
} 

void RRGamePlay::Move(Unit* who, const Vector2& at) {
	// на момент вызова мы полагаем, что это полностью валидные координаты и объект 
	ObjectType type = world->CheckPosition(at);
	if (type == ObjectType::ground) { // только земля проходима
		// поэтому пытаемся туда пойти 
		who->SetTask(new TaskMove(at));
	}
	// здания и юниты непроходимы, если это свои
	else if (type == ObjectType::unit) {
		if (world->GetUnitAt(at)->GetMaster() != who->GetMaster()) // объекты разных игроков
		{
			/*атака по юниту*/
		}
	}
	else if (type == ObjectType::building) {
		Building* building = world->GetBuildingAt(at);
		if (building->GetMaster() == who->GetMaster()) // объекты одного игрока
		{
			// если здание строится и выбран рабочий 
			if (building->GetUnderConstruction() && who->GetType() == UnitType::worker) {
				// для строительства рабочий должен стоять на соседней клетке со зданием
				auto ground = GetGroundIn(at, 1, world->GetSize()); 
				auto iter = ground.find(who->GetPosition());
				if (iter != ground.end()) { // если он стоит рядом, то отдаём приказ
					who->SetTask(new TaskBuildProduction{ building->GetType(), building->GetPosition() });
				}
			}
		}
		else {// объекты разных игроков
			/*атака по зданию*/
		}
	}
	// и их можно атаковать, если это вражеские 
	/*
	проверить, нужно ли подойти, чтобы атаковать. если нужно, то MoveToAttack
	если не нужно, то Attack
	это дело требует компоненты HasAttack
	*/ 
}

void RRGamePlay::MoveToAttack(Unit* who, const Vector2& at) {

}

void RRGamePlay::Attack(Unit* who, const Vector2& at) {

}

void RRGamePlay::ProductionPhase() {
	for (auto& iter : world->GetLevel()->units)
		iter.second->ProductionPhase();
	for (auto& iter : world->GetLevel()->buildings)
		iter.second->ProductionPhase();
} 
 
 