#pragma once
#include <SDL.h>
#include "Vector2.h" 
#include "Rectangle.h"

// ���������� ��� ������, ������ ��� �������� ��������
struct MakeTextureInfo
{
	SDL_Renderer* renderer;
}; 

/*
���������� ��������
*/
class RRTexture
{
public:
	RRTexture() : texture(nullptr) {} 
	RRTexture(SDL_Texture* texture) : texture(texture) {}

	// ������������ ������ ��������
	void Destroy() {
		SDL_DestroyTexture(texture);
	}

	// �������� �������� �� ����� path
	bool Load(const char* path, MakeTextureInfo info);

	// ������ �������� X - Width, Y - Height
	Vector2 GetSize() const;
	 

	// �������� ������ �������� ��� ���������
	SDL_Texture* Get() const { return texture; };
private:
	SDL_Texture* texture;
};

