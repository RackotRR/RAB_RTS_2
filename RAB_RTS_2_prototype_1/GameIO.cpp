#include "GameIO.h"
#include "GameIO_SDL.h"

GameIO* GameIO::Instance() {
	static GameIO_SDL instance;
	return &instance;
}

