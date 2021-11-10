#include "RRTexture.h"
#include <SDL_image.h>

// �������� �������� �� ����� ��� ������ SDL_image
bool RRTexture::Load(const char* path, MakeTextureInfo info) {

	SDL_Surface* surface = IMG_Load(path);
	if (!surface) {
		SDL_Log("Failed to load texture file %s", path);
		return false;
	}

	texture = SDL_CreateTextureFromSurface(info.renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture) {
		SDL_Log("Failed to convert surface to texture for %s", path);
		return false;
	}

	return true;
}


Vector2 RRTexture::GetSize() const {
	// ���������� �������� � � ����������. ���������� ������ ��������
	Vector2 size;
	SDL_QueryTexture(texture, nullptr, nullptr, &size.X, &size.Y); 
	return size;
}