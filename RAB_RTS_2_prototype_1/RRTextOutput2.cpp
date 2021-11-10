#include "RRTextOutput2.h"
#include <limits>

RRTextOutput2* RRTextOutput2::Instance() {
	static RRTextOutput2 instance;
	return &instance;
}

bool RRTextOutput2::Initialize(SDL_Renderer* renderer) {
	// ���� TTF ��� ���������������, �� �� ����� ���������������� ��� �����
	if (TTF_WasInit()) return true;

	// ��������������
	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init: %s", TTF_GetError());
		return false; // ������
	}
	  
	this->renderer = renderer;

	// �������������� ������
	if (!InitFonts())
		return false;

	return true;
}

void RRTextOutput2::Shutdown() {
	for (auto& iter : renderedFonts) { // iter - ��������� �� ����������� char � RRTexture*
		for (auto& i : (*iter.second)) { // i - ���� char � RRTexture
			i.second->Destroy(); // ����������� ������ � RRTexture*
			delete i.second; // ������� ��������� �� RRTexture
		}
		delete iter.second; // ������� ��������� �� ����������� char � RRTexture*
	}

	// ��������� SDL_ttf
	if (TTF_WasInit())
		TTF_Quit();
}

bool RRTextOutput2::InitFonts() {
	if (!LoadFont(Font::Treasures, "Fonts\\FreeMono.ttf", 24, RRColor(255, 255, 255), TTF_STYLE_BOLD))
		return false;
	/*
	��������� ����� ����� ������
	*/
	return true;
}

bool RRTextOutput2::LoadFont(Font key, const std::string& path, int size, const RRColor& color, int styleFlags) {
	TTF_Font* font;
	// ��������� �����
	font = TTF_OpenFont(path.c_str(), size);
	if (!font) { // ���� �� ����������
		SDL_Log("TTF_OpenFont: %s", TTF_GetError());
		return false;
	}

	// ��������� �����
	if (styleFlags != TTF_STYLE_NORMAL)
		TTF_SetFontStyle(font, styleFlags);

	// ��������� � ������ �������
	fonts[key] = font;
	if (!RenderFont(key, color))
		return false;
	
	 
	return true;
}

bool RRTextOutput2::RenderFont(Font font, const RRColor& c) {
	char glyph[2]; // ��-������ ���� "?\0"
	glyph[1] = '\0'; // ������� ��-������ ������ ������������� \0

	SDL_Color color = { c.r, c.g, c.b, c.a }; // white 

	SDL_Surface* surface;  
	SDL_Texture* texture; 
	RRTexture* rrtexture;
	auto textureMap = new std::unordered_map<char, RRTexture*>;

	// �������� ���������� ������� � �����
	for (char i = 32; i < 127; i++) { 
		surface = nullptr;
		texture = nullptr;
		rrtexture = nullptr;

		glyph[0] = i; // ������ ��� �������

		// �������� ����������� ����� �� surface
		surface = TTF_RenderUTF8_Blended(fonts[font], glyph, color);
		if (surface == nullptr) {
			SDL_Log("TTF_RenderUTF8_Blended fault: %s", TTF_GetError());
			return false;
		}

		// �������� ������� �� surface �������� ��� ����������� �������������
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr) {
			SDL_Log("SDL_CreateTextureFromSurface fault: %s", SDL_GetError());
			return false;
		}

		// ����������� �������� � RRTexture
		rrtexture = new RRTexture(texture);
		// ��������� � ������ �������
		(*textureMap)[i] = rrtexture;
	}
	// ��������� ���������� ������ � �����
	renderedFonts[font] = textureMap;
	return true;
}

RRTexture* RRTextOutput2::GetTextureFrom(Font font, const char& c) {
	// �������� �������� ��� ��������� �������
	return renderedFonts[font]->at(c);
}

void RRTextOutput2::DrawLine(const Vector2& topleft, Font font, const std::string& str) {
	if (str == "FF") {
		int a = 1 + 2;
	}
	// ����������� �������� �� ������ � �������� ������ ������
	for (int i = 0; i < str.size(); i++) { 
		RRTexture* texture = GetTextureFrom(font, str[i]);
		Vector2 size = texture->GetSize();
		SDL_Rect rect = { topleft.X + i * size.X, topleft.Y, size.X, size.Y };
		SDL_RenderCopy(renderer, texture->Get(), nullptr, &rect);
	}
} 