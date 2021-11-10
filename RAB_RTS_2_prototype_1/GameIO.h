#pragma once
#include <string>
#include "Vector2.h"
#include "Rectangle.h"
#include "RRMouse.h"
#include "KeyboardState.h"
#include "RRColor.h"
#include "RRTexture.h"

enum class DrawFlip {
	none = 0,
	horizontal,
	vertical,
};

enum class Font {
	Menu,
	Treasures
};

class GameIO {
public:
	static GameIO* Instance();
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Begin() = 0;
	virtual void End() = 0;

	virtual void UpdateInput() = 0;
	virtual double GetTicks() const = 0;

	virtual int GetWinWidth() const = 0;
	virtual int GetWinHeight() const = 0;

	virtual const KeyboardState& GetKeyState() const = 0;
	virtual const RRMouse& GetMouseState() const = 0;

	// нарисовать текстуру
	virtual void DrawTexture(const Rectangle& rect, RRTexture* texture) = 0;
	// нарисовать текстуру с поворотом
	virtual void DrawTexture(const Rectangle& rect, RRTexture* texture, double angle) = 0;
	// нарисовать текстуру с поворотом и отражением
	virtual void DrawTexture(const Rectangle& rect, RRTexture* texture, double angle, DrawFlip dflip) = 0;

	// вывести строку на экран
	virtual void DrawLine(const Vector2& topLeft, Font font, const std::string& str) = 0;

	// нарисовать прямоугольник
	virtual void DrawRectangle(const Rectangle& rect, const RRColor& color) = 0;
protected:
	GameIO() {}
	GameIO(const GameIO&) = delete;
	GameIO& operator= (const GameIO&) = delete;
	virtual ~GameIO() {}
};

