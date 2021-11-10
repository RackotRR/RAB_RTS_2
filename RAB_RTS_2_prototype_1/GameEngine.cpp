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
	 
	// ������������� GameIO
	gameIO = GameIO::Instance();
	if (!gameIO->Initialize()) return false; 

	// ������������� ��������� ���������, �������� ���� 
	world = GameFIO::Load("map_1.rrrts2map");

	// ������������� ������������ ������
	gameplay = new RRGamePlay(world);



	// ������������� �������
	Player* ptr = new Player;
	ptr->Initialize(gameplay, world->GetPlayerData(0));
	players.push_back(ptr);

	ptr = new Player;
	ptr->Initialize(gameplay, world->GetPlayerData(1));
	players.push_back(ptr);

	ObjectsFactory* objectsFactory = ObjectsFactory::Instance();
	objectsFactory->Initialize(world, &players);
	

	// �������������� gameplay ����� ����, ��� ���� ��������� ��� ������
	gameplay->Initialize();
	return true;
}
 

void GameEngine::Shutdown() { 
	// ��������� ������ ������ � �������� �������
	for (auto iter : players) {
		iter->Shutdown();
		delete iter;
	}

	gameplay->Shutdown();

	delete world; 
	gameIO->Shutdown(); 
}

void GameEngine::Run() {
	while (true) // ��������� �� �����, ���� ���-�� �� ����� ����� �� ����
	{
		gameplay->ProductionPhase();
		for (currentPlayer = 0; currentPlayer < players.size(); ++currentPlayer) { // ������ �������� - ��� ������ ������
			CurrentPlayer().StartTurn();
			do { // ������������ �������� ������, ���� �� �� �������� ���
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
	  
	// ���� ����� �� ���� �������������� ���. � ������� - ����������!
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