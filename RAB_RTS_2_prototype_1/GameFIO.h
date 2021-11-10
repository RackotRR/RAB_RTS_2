#pragma once
#include <string> 
#include "World.h" 
#include <fstream>

using std::string;
using std::ifstream;

/*
�����, ���������� �� ���������� � �������� ������ �� ������.
����� ����� � ���������� ������������, �������� � ����������� ���������
*/
class GameFIO
{
public: 
	GameFIO() = delete;
	// ��������� ��� � ����� path
	static void Save(string path, const World* world); 

	// ��������� ���. ���������� nullptr � ������ �������
	// ��������� ������� World* ����� ���������� ������ � ���
	static World* Load(string path);

private:
	static void LoadUnits(ifstream& stream, Level& level);
	static void LoadBuildings(ifstream& stream, Level& level);
	static void LoadResources(ifstream& stream, Level& level);
};

