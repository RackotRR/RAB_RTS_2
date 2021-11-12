#include "HasTexture.h"
#include <cassert>
#include "RRTexture.h"

HasTexture::HasTexture() : currentTexture{ 0 } 
{

}

HasTexture::HasTexture(RRTexture* texture) : 
	currentTexture{ 0 }
{
	AddTexture(texture);
}

void HasTexture::AddTexture(RRTexture* texture) {
	textures.push_back(texture);
}

RRTexture* HasTexture::GetTexture(int num) const {
	assert(num < textures.size() && num >= 0);
	return textures[num];
}

RRTexture* HasTexture::GetTexture() const {
	assert(currentTexture < textures.size() && currentTexture >= 0);
	return textures[currentTexture];
}

void HasTexture::ChangeCurrentTexture(int num) {
	currentTexture = num;
}

int HasTexture::GetTexturesNum() const {
	return static_cast<int>(textures.size());
}