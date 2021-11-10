#pragma once
class Building;
class UnderConstruction
{
public: 
	// задаёт кол-во очков, которые нужно потратить на строительство
	// перед вызовом этого метода текстуры уже должны быть прикреплены к зданию!
	void SetPointsToConstruct(int toConstruct, Building* building);

	// возвращает кол-во очков, которые осталось потратить, чтобы построить здание
	int GetUnderConstruction() const;

	// отстроить здание на val очков
	// возвращает true, если здание было построено
	bool Construct(int val);
private:
	void UpdateTexture();
	// по умолчанию 0 - отстроенное состояние
	int underConstruction = 0; 
	int toConstruct = 0;
	Building* building = nullptr;
};

