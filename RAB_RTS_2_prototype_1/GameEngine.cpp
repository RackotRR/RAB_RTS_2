 #include "GameEngine.h"
#include "RRGamePlay.h"
#include "GameIO.h"
#include "GameFIO.h" 
#include "RRTextureManager.h"
#include "World.h" 
#include "Player.h"
#include "PlayerTreasures.h"
#include "ObjectsFactory.h"


GameEngine* GameEngine::Instance() {
	static GameEngine instance;
	return &instance;
}

bool GameEngine::Initialize() { 
	shouldQuit = false;  
	 
	// инициализация GameIO
	gameIO = GameIO::Instance();
	if (!gameIO->Initialize()) return false; 

	// Инициализация файлового менеджера, загрузка мира 
	world = GameFIO::Load("map_1.rrrts2map");

	// инициализация геймплейного модуля
	gameplay = new RRGamePlay(world);



	// инициализация игроков
	Player* ptr = new Player;
	ptr->Initialize(gameplay, world->GetPlayerData(0));
	players.push_back(ptr);

	ptr = new Player;
	ptr->Initialize(gameplay, world->GetPlayerData(1));
	players.push_back(ptr);

	ObjectsFactory* objectsFactory = ObjectsFactory::Instance();
	objectsFactory->Initialize(world, &players);
	

	// инициализируем gameplay после того, как были загружены все данные
	gameplay->Initialize();
	return true;
}
 

void GameEngine::Shutdown() { 
	// завершаем работу систем в обратном порядке
	for (auto iter : players) {
		iter->Shutdown();
		delete iter;
	}

	gameplay->Shutdown();

	delete world; 
	gameIO->Shutdown(); 
}

void GameEngine::Run() {
	while (true) // повторяем по кругу, пока кто-то не нажмёт выход из игры
	{
		gameplay->ProductionPhase();
		for (currentPlayer = 0; currentPlayer < players.size(); ++currentPlayer) { // каждая итерация - ход одного игрока
			CurrentPlayer().StartTurn();
			do { // обрабатываем действия игрока, пока он не закончит ход
				ProcessInput();
				Update();
				GenerateOutput();
				if (shouldQuit) return;
			} while (!CurrentPlayer().Finished());
		}
	}
}
 
void GameEngine::ProcessInput() {
	gameIO->UpdateInput();

	RRMouse mouse = gameIO->GetMouseState();
	const KeyboardState& keyState = gameIO->GetKeyState();
	  
	// пока выход из игры осуществляется так. в будущем - переделать!
	if (keyState.IsKeyDown(Keys::ESCAPE)) shouldQuit = true; 

	CurrentPlayer().ProcessInput(mouse, keyState);
}

void GameEngine::Update() {
	CurrentPlayer().Update();
}

void GameEngine::GenerateOutput() {
	gameIO->Begin(); 
	CurrentPlayer().GenerateOutput();
	gameIO->End();
}