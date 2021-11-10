#pragma once
#include <unordered_map>
#include <string>
#include "RRTexture.h"
#include "TextureType.h"

using std::string;
using std::unordered_map;


/*
класс для загрузки, получения и выгрузки текстур
*/
class RRTextureManager
{
public:
	static RRTextureManager* Instance() {
		static RRTextureManager instance;
		return &instance;
	}
	// вызвать для начала работы
	bool Initialize(MakeTextureInfo info); 

	// вызвать для завершения работы
	void Shutdown();

	// получить текстуру по ключу 
	RRTexture* GetTexture(TextureType type);
private:
	RRTextureManager() {}
	RRTextureManager(const RRTextureManager&) = delete;
	RRTextureManager operator=(const RRTextureManager&) = delete;

	// загрузить текстуру из файла
	RRTexture LoadTexture(const string& path);
	 
	unordered_map<TextureType, RRTexture*> textures;
	MakeTextureInfo info;
};

