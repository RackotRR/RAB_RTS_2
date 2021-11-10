#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector2.h"
#include "RRColor.h" 
#include "RRTexture.h"
#include "GameIO.h"
#include <unordered_map>
#include <string>

class RRTextOutput2
{
public:
	static RRTextOutput2* Instance();

	// ���������������� ���� �������� ����� GameIO
	bool Initialize(SDL_Renderer* renderer);

	// ������� ��� ������������ ������
	void Shutdown();

	// ������� �� ����� ������ ��������� �������
	void DrawLine(const Vector2& topleft, Font font, const std::string& str);
private:
	// �������� �� �������� ���������� ������ ��������
	RRTexture* GetTextureFrom(Font font, const char& c);

	// ��������� ����� � ��������� �����������
	bool LoadFont(Font key, const std::string& path, int size, const RRColor& color, int styleFlags = 0);
	
	// �������������� ��� ������. �������� ����� �� ��������������
	/*
	����� ������ ��������� �����!!!
	*/
	bool InitFonts();

	// �������� ��� ������ ������� � ���� �������
	bool RenderFont(Font font, const RRColor& c);

	SDL_Renderer* renderer;
	std::unordered_map<Font, TTF_Font*> fonts;
	std::unordered_map<Font, std::unordered_map<char, RRTexture*>*> renderedFonts;
	 
	RRTextOutput2() : renderer(nullptr) {}
	~RRTextOutput2() {}

	RRTextOutput2(const RRTextOutput2&) = delete;
	RRTextOutput2& operator=(const RRTextOutput2) = delete;
};

