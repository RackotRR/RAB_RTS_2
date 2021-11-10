#pragma once 
class Player;
/*
Компонента для объектов, у которых есть хозяин (master). Такие объекты должны наследовать этот класс
*/
class HasMaster
{
public:
	// Master - указатель на игрока-хозяина (в процессе игры)
	void SetMaster(Player* player);
	Player* GetMaster();

	// Owner - условный номер игрока в списке (вне игры, при загрузке или сохранении, отрисовке)
	void SetOwner(size_t owner);
	size_t GetOwner() const;
private:
	Player* master;
	size_t owner;
};

