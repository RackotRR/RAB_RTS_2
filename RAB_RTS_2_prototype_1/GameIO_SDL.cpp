#include "GameIO_SDL.h"
#include "RRTextOutput2.h"
#include "RRTextureManager.h"
#include <SDL_image.h>

GameIO_SDL::GameIO_SDL() : GameIO(), window(nullptr), renderer(nullptr),
windowWidth(), windowHeight(), previousFrameTicks(), currentFrameTicks(),
frameTicksDifference() {

}

bool GameIO_SDL::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_Rect displayBounds;
	if (SDL_GetDisplayBounds(0, &displayBounds) != 0) {
		SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
		return false;
	}
	else {
		windowHeight = displayBounds.h * 0.8;
		windowWidth = displayBounds.w * 0.8;
	}

	window = SDL_CreateWindow("Red&Blue: Road to Space II", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_VULKAN | SDL_WINDOW_BORDERLESS);
	if (!window) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// режим прозрачности
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD) != 0) {
		SDL_Log("Failed to set render draw blend mode: %s", SDL_GetError());
		return false;
	}

	// модуль для загрузки текстур в PNG
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (!RRTextureManager::Instance()->Initialize({ renderer }))
		return false;

	// модуль для вывода генерации текстур из текста
	if (!RRTextOutput2::Instance()->Initialize(renderer))
		return false;

	return true;
}
void GameIO_SDL::Shutdown() {
	RRTextOutput2::Instance()->Shutdown();
	RRTextureManager::Instance()->Shutdown();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameIO_SDL::Begin() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
void GameIO_SDL::End() {
	int FPS = 1000 / (currentFrameTicks - previousFrameTicks);
	DrawLine(Vector2(windowWidth - 50, 0), Font::Treasures, std::to_string(FPS));
	SDL_RenderPresent(renderer);
}

void GameIO_SDL::UpdateInput() {
	previousFrameTicks = currentFrameTicks; // сохраняем предыдущее значение
	currentFrameTicks = SDL_GetTicks(); // кол-во милисекунд, прошедших с запуска программы 
	frameTicksDifference = (currentFrameTicks - previousFrameTicks) * 0.001; // промежуток времени между вызовами этого метода
	// сохраняем предыдущее состояние мыши
	mouseState.SavePrevious();

	// получаем события от системы
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) { // событие нажатия кнопки на мышке
			if (event.button.button == SDL_BUTTON_LEFT) // ЛКМ
				mouseState.LeftButton = MouseState::Pressed;
			if (event.button.button == SDL_BUTTON_RIGHT) // ПКМ
				mouseState.RightButton = MouseState::Pressed;
		}
		if (event.type == SDL_MOUSEBUTTONUP) { // событие отжатия кнопки на мышке
			if (event.button.button == SDL_BUTTON_LEFT)
				mouseState.LeftButton = MouseState::Released;
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseState.RightButton = MouseState::Released;
		}
		if (event.type == SDL_MOUSEMOTION) { // событие движение мыши
			mouseState.Position = Vector2(event.motion.x, event.motion.y);
		}
	}

	// получаем данные ввода с клавиатуры
	keyState.Update((unsigned char*)SDL_GetKeyboardState(NULL));
}
double GameIO_SDL::GetTicks() const {
	return frameTicksDifference;
}

int GameIO_SDL::GetWinWidth() const {
	return windowWidth;
}
int GameIO_SDL::GetWinHeight() const {
	return windowHeight;
}

const KeyboardState& GameIO_SDL::GetKeyState() const {
	return keyState;
}
const RRMouse& GameIO_SDL::GetMouseState() const {
	return mouseState;
}

// нарисовать текстуру
void GameIO_SDL::DrawTexture(const Rectangle& rect, RRTexture* texture) {
	DrawTexture(rect, texture, 0, DrawFlip::none);
}
// нарисовать текстуру с поворотом
void GameIO_SDL::DrawTexture(const Rectangle& rect, RRTexture* texture, double angle) {
	DrawTexture(rect, texture, angle, DrawFlip::none);
}
// нарисовать текстуру с поворотом и отражением
void GameIO_SDL::DrawTexture(const Rectangle& rect, RRTexture* texture, double angle, DrawFlip dflip) {
	SDL_Rect r = { rect.x, rect.y, rect.width, rect.height }; // где мы будем рисовать

	SDL_RendererFlip flip; // отражение
	switch (dflip)
	{
	case DrawFlip::horizontal:
		flip = SDL_FLIP_HORIZONTAL;
		break;
	case DrawFlip::vertical:
		flip = SDL_FLIP_VERTICAL;
		break;
	default:
		flip = SDL_FLIP_NONE;
		break;
	}

	// рисуем
	SDL_RenderCopyEx(renderer,
		texture->Get(), // текстурка
		nullptr, // вся текстура
		&r, // где
		angle, // угол поворота
		nullptr, // относительно центра
		flip); // отражение
}

// вывести строку на экран
void GameIO_SDL::DrawLine(const Vector2& topLeft, Font font, const std::string& str) {
	RRTextOutput2::Instance()->DrawLine(topLeft, font, str);
}

// нарисовать прямоугольник
void GameIO_SDL::DrawRectangle(const Rectangle& rect, const RRColor& color) {
	SDL_Rect r = { rect.x, rect.y, rect.width, rect.height };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &r);
}
