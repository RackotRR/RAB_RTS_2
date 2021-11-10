#include "HasHP.h" 
#include <assert.h>

HasHP::HasHP() : maxHP(), hp() {}

int HasHP::Heal(int val) {
	assert(val >= 0);

	hp += val;

	if (hp > maxHP)
		hp = maxHP; // если здоровье окажется больше максимального
	return hp;
}
 
int HasHP::MakeDamage(int val) {
	assert(val >= 0);

	hp -= val; 
	return hp;
}


bool HasHP::IsDead() const {
	return (hp <= 0);
}

int HasHP::GetMaxHP() const {
	return maxHP;
}
int HasHP::GetHP() const { 
	return hp;
}
void HasHP::SetMaxHP(int newValue) { 
	maxHP = newValue; 
}
void HasHP::SetHP(int newValue) { 
	hp = newValue; 
}
void HasHP::InitHP() {
	hp = maxHP; 
}