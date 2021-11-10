#pragma once
class Building;
class UnderConstruction
{
public: 
	// ����� ���-�� �����, ������� ����� ��������� �� �������������
	// ����� ������� ����� ������ �������� ��� ������ ���� ����������� � ������!
	void SetPointsToConstruct(int toConstruct, Building* building);

	// ���������� ���-�� �����, ������� �������� ���������, ����� ��������� ������
	int GetUnderConstruction() const;

	// ��������� ������ �� val �����
	// ���������� true, ���� ������ ���� ���������
	bool Construct(int val);
private:
	void UpdateTexture();
	// �� ��������� 0 - ����������� ���������
	int underConstruction = 0; 
	int toConstruct = 0;
	Building* building = nullptr;
};

