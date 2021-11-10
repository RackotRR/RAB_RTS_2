#pragma once
#include <vector>

using std::vector;
class GameIO;
class RRTextureManager;
class Player;
class World;
class RRGamePlay;

/// <summary>
/// Основной класс игры. Связующее звено между модулями игры
/// </summary>
class GameEngine 
{
public:
	/// <summary>
	/// инициализирует все модули игры
	/// </summary>
	/// <returns>true, если объект был инициализирован</returns>
	bool Initialize(); 

	// запускает основной цикл игры
	void Run(); 
	 
	// закрывает все модули игры 
	void Shutdown(); 

	static GameEngine* Instance();
private:
	GameEngine() = default;
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator= (const GameEngine) = delete;
	// загрузка, получение, выгрузка текстур
	RRTextureManager* textureManager;

	// отрисовка
	GameIO* gameIO;

	// если true, то программа завершает работу
	bool shouldQuit;
	 
	// получение входных данных
	void ProcessInput();  
	// обработка полученной информации
	void Update();  
	// вывод данных
	void GenerateOutput(); 
	  
	vector<Player*> players;
	int currentPlayer;

	/// <summary>
	/// возвращает ссылку на текущего игрока
	/// </summary>
	Player& CurrentPlayer() { 
		return *(players[currentPlayer]); 
	}

	// данные о мире
	World* world;

	RRGamePlay* gameplay;
};

