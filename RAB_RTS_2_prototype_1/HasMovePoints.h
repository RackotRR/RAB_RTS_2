#pragma once
#include <assert.h> 
class HasMovePoints  
{
public:
	HasMovePoints();
	int GetMovePoints() const;
	int GetMaxMovePoints() const;

	void SetMaxMovePoints(int val);
	void SetMovePoints(int val);

	void ResetMovePoints();

	// ����� false, ���� ���� ����������� ����������
	bool TryToSpendMovePoints(int val = 1);
private:   
	int movePoints;
	int maxMovePoints;

};

