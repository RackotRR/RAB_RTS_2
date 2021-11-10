 #include <iostream>
#include "GameEngine.h"
#include <SDL.h>

int main(int argc, char* argv[])
{  
    GameEngine* e = GameEngine::Instance();
    if (e->Initialize()) {
        e->Run();
        e->Shutdown();
    }
    return 0;
} 