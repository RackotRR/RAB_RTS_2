#pragma once
#include <SDL.h>
#include "GameIO.h"
class GameIO_SDL : public GameIO
{
public:
	GameIO_SDL();
	bool Initialize() override;
	void Shutdown() override;

	void Begin() override;
	void End() override;

	void UpdateInput() override;
	double GetTicks() const override;

	int GetWinWidth() const override;
	int GetWinHeight() const override;

	const KeyboardState& GetKeyState() const override;
	const RRMouse& GetMouseState() const override;

	// ���������� ��������
	void DrawTexture(const Rectangle& rect, RRTexture* texture) override;
	// ���������� �������� � ���������
	void DrawTexture(const Rectangle& rect, RRTexture* texture, double angle) override;
	// ���������� �������� � ��������� � ����������
	void DrawTexture(const Rectangle& rect, RRTexture* texture, double angle, DrawFlip dflip) override;

	// ������� ������ �� �����
	void DrawLine(const Vector2& topLeft, Font font, const std::string& str) override;

	// ���������� �������������
	void DrawRectangle(const Rectangle& rect, const RRColor& color) override;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int windowWidth, windowHeight;

	RRMouse mouseState;
	KeyboardState keyState;

	Uint32 previousFrameTicks;
	Uint32 currentFrameTicks;
	double frameTicksDifference;
};

