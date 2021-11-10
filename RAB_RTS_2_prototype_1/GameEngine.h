#pragma once
#include <vector>

using std::vector;
class GameIO;
class RRTextureManager;
class Player;
class World;
class RRGamePlay;

/// <summary>
/// �������� ����� ����. ��������� ����� ����� �������� ����
/// </summary>
class GameEngine 
{
public:
	/// <summary>
	/// �������������� ��� ������ ����
	/// </summary>
	/// <returns>true, ���� ������ ��� ���������������</returns>
	bool Initialize(); 

	// ��������� �������� ���� ����
	void Run(); 
	 
	// ��������� ��� ������ ���� 
	void Shutdown(); 

	static GameEngine* Instance();
private:
	GameEngine() = default;
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator= (const GameEngine) = delete;
	// ��������, ���������, �������� �������
	RRTextureManager* textureManager;

	// ���������
	GameIO* gameIO;

	// ���� true, �� ��������� ��������� ������
	bool shouldQuit;
	 
	// ��������� ������� ������
	void ProcessInput();  
	// ��������� ���������� ����������
	void Update();  
	// ����� ������
	void GenerateOutput(); 
	  
	vector<Player*> players;
	int currentPlayer;

	/// <summary>
	/// ���������� ������ �� �������� ������
	/// </summary>
	Player& CurrentPlayer() { 
		return *(players[currentPlayer]); 
	}

	// ������ � ����
	World* world;

	RRGamePlay* gameplay;
};

