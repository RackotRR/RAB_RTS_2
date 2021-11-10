#include "RRTextOutput2.h"
#include <limits>

RRTextOutput2* RRTextOutput2::Instance() {
	static RRTextOutput2 instance;
	return &instance;
}

bool RRTextOutput2::Initialize(SDL_Renderer* renderer) {
	// если TTF был инициализирован, то не будем инициализировать его снова
	if (TTF_WasInit()) return true;

	// инициализируем
	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init: %s", TTF_GetError());
		return false; // ошибка
	}
	  
	this->renderer = renderer;

	// инициализируем шрифты
	if (!InitFonts())
		return false;

	return true;
}

void RRTextOutput2::Shutdown() {
	for (auto& iter : renderedFonts) { // iter - указатель на отображение char в RRTexture*
		for (auto& i : (*iter.second)) { // i - пара char и RRTexture
			i.second->Destroy(); // освобождаем память в RRTexture*
			delete i.second; // удаляем указатель на RRTexture
		}
		delete iter.second; // удаляем указатель на отображение char в RRTexture*
	}

	// закрываем SDL_ttf
	if (TTF_WasInit())
		TTF_Quit();
}

bool RRTextOutput2::InitFonts() {
	if (!LoadFont(Font::Treasures, "Fonts\\FreeMono.ttf", 24, RRColor(255, 255, 255), TTF_STYLE_BOLD))
		return false;
	/*
	добавялем здесь новые шрифты
	*/
	return true;
}

bool RRTextOutput2::LoadFont(Font key, const std::string& path, int size, const RRColor& color, int styleFlags) {
	TTF_Font* font;
	// загружаем шрифт
	font = TTF_OpenFont(path.c_str(), size);
	if (!font) { // если не получилось
		SDL_Log("TTF_OpenFont: %s", TTF_GetError());
		return false;
	}

	// добавляем стили
	if (styleFlags != TTF_STYLE_NORMAL)
		TTF_SetFontStyle(font, styleFlags);

	// добавляем в список шрифтов
	fonts[key] = font;
	if (!RenderFont(key, color))
		return false;
	
	 
	return true;
}

bool RRTextOutput2::RenderFont(Font font, const RRColor& c) {
	char glyph[2]; // си-строка вида "?\0"
	glyph[1] = '\0'; // входная си-строка должна заканчиваться \0

	SDL_Color color = { c.r, c.g, c.b, c.a }; // white 

	SDL_Surface* surface;  
	SDL_Texture* texture; 
	RRTexture* rrtexture;
	auto textureMap = new std::unordered_map<char, RRTexture*>;

	// рендерим английский алфавит и знаки
	for (char i = 32; i < 127; i++) { 
		surface = nullptr;
		texture = nullptr;
		rrtexture = nullptr;

		glyph[0] = i; // символ для рендера

		// пытаемся отрендерить текст на surface
		surface = TTF_RenderUTF8_Blended(fonts[font], glyph, color);
		if (surface == nullptr) {
			SDL_Log("TTF_RenderUTF8_Blended fault: %s", TTF_GetError());
			return false;
		}

		// пытаемся сделать из surface текстуру для дальнейшего использования
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr) {
			SDL_Log("SDL_CreateTextureFromSurface fault: %s", SDL_GetError());
			return false;
		}

		// оборачиваем текстуру в RRTexture
		rrtexture = new RRTexture(texture);
		// добавляем в массив текстур
		(*textureMap)[i] = rrtexture;
	}
	// добавляем полученный массив в общий
	renderedFonts[font] = textureMap;
	return true;
}

RRTexture* RRTextOutput2::GetTextureFrom(Font font, const char& c) {
	// получаем текстуру для заданного символа
	return renderedFonts[font]->at(c);
}

void RRTextOutput2::DrawLine(const Vector2& topleft, Font font, const std::string& str) {
	if (str == "FF") {
		int a = 1 + 2;
	}
	// посимвольно проходим по строке и рендерим каждый символ
	for (int i = 0; i < str.size(); i++) { 
		RRTexture* texture = GetTextureFrom(font, str[i]);
		Vector2 size = texture->GetSize();
		SDL_Rect rect = { topleft.X + i * size.X, topleft.Y, size.X, size.Y };
		SDL_RenderCopy(renderer, texture->Get(), nullptr, &rect);
	}
} 