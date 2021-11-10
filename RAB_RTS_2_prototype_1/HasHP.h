#pragma once 
/*
Компонента для здоровья. Объекты, обладающие здоровьем должны наследовать этот класс.
Позволяет наносить урон объекту и лечить его. Если здоровье опустится ниже 0, объект должен быть уничтожен
*/
class HasHP  
{
public: 
    HasHP();

    // нанести урон по объекту (value >= 0). возвращает кол-во оставшегося здоровья
    int MakeDamage(int damage);

    // вылечить объект на value пунктов (value >= 0). возвращает кол-во оставшегося здоровья
    int Heal(int value); 
     
    bool IsDead() const;

    int GetMaxHP() const;
    int GetHP() const;
    void SetMaxHP(int newValue);
    void SetHP(int newValue);

    // устанавливает текущее здоровье равным максимальному
    void InitHP();
private: 
    int maxHP, hp;
};

