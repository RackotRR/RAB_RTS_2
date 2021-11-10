#pragma once
#include "HasTexture.h"
#include "Rectangle.h"
#include <string>

class RRTexture;

class ContentField : public HasTexture
{
public:
	ContentField(const Rectangle& rect);
	~ContentField() {}

	void SetTexture(RRTexture* texture);
	void SetText(std::string text);

	void GenerateOutput();

	const Rectangle& GetRect() const;
private:
	std::string text;
	Rectangle rect; 
};

