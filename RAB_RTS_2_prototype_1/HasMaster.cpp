#include "HasMaster.h"
#include "Player.h"
 
void HasMaster::SetMaster(Player* player) {
	master = player;
}

Player* HasMaster::GetMaster() {
	return master;
}
 
void HasMaster::SetOwner(size_t owner) {
	this->owner = owner;
}
size_t HasMaster::GetOwner() const {
	return owner;
}