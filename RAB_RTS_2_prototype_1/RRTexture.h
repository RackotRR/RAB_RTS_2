#pragma once
#include <SDL.h>
#include "Vector2.h" 
#include "Rectangle.h"

// Абстракция для данных, нужных для создания текстуры
struct MakeTextureInfo
{
	SDL_Renderer* renderer;
}; 

/*
Абстракция текстуры
*/
class RRTexture
{
public:
	RRTexture() : texture(nullptr) {} 
	RRTexture(SDL_Texture* texture) : texture(texture) {}

	// Освобождения памяти текстуры
	void Destroy() {
		SDL_DestroyTexture(texture);
	}

	// загрузка текстуры из файла path
	bool Load(const char* path, MakeTextureInfo info);

	// размер картинки X - Width, Y - Height
	Vector2 GetSize() const;
	 

	// получить данные текстуры для отрисовки
	SDL_Texture* Get() const { return texture; };
private:
	SDL_Texture* texture;
};

