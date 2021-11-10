#pragma once
#include <vector>

class RRTexture;

class HasTexture
{
public:
	HasTexture();
	HasTexture(RRTexture* texture);
	void AddTexture(RRTexture* texture);
	RRTexture* GetTexture(int num) const;
	RRTexture* GetTexture() const;
	void ChangeCurrentTexture(int num);
protected:
	int GetTexturesNum() const;
private: 
	int currentTexture;
	std::vector<RRTexture*> textures;
};

