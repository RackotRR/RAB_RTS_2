#pragma once
#include <unordered_map>
#include <string>
#include "RRTexture.h"
#include "TextureType.h"

using std::string;
using std::unordered_map;


/*
����� ��� ��������, ��������� � �������� �������
*/
class RRTextureManager
{
public:
	static RRTextureManager* Instance() {
		static RRTextureManager instance;
		return &instance;
	}
	// ������� ��� ������ ������
	bool Initialize(MakeTextureInfo info); 

	// ������� ��� ���������� ������
	void Shutdown();

	// �������� �������� �� ����� 
	RRTexture* GetTexture(TextureType type);
private:
	RRTextureManager() {}
	RRTextureManager(const RRTextureManager&) = delete;
	RRTextureManager operator=(const RRTextureManager&) = delete;

	// ��������� �������� �� �����
	RRTexture LoadTexture(const string& path);
	 
	unordered_map<TextureType, RRTexture*> textures;
	MakeTextureInfo info;
};

