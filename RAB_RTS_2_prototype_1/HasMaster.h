#pragma once 
class Player;
/*
���������� ��� ��������, � ������� ���� ������ (master). ����� ������� ������ ����������� ���� �����
*/
class HasMaster
{
public:
	// Master - ��������� �� ������-������� (� �������� ����)
	void SetMaster(Player* player);
	Player* GetMaster();

	// Owner - �������� ����� ������ � ������ (��� ����, ��� �������� ��� ����������, ���������)
	void SetOwner(size_t owner);
	size_t GetOwner() const;
private:
	Player* master;
	size_t owner;
};

