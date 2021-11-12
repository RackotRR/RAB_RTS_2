#include <cassert>
#include "ContentField.h"
#include "GameIO.h"
#include "RRTextureManager.h"


ContentField::ContentField(const Rectangle& rect) : HasTexture(), rect(rect), text() {
	AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::field));
} 

void ContentField::SetTexture(RRTexture* texture) {
	AddTexture(texture);
}
void ContentField::SetText(string text) { 
	this->text = text; 
}

void ContentField::GenerateOutput() {
	GameIO::Instance()->DrawTexture(rect, GetTexture(0));

	assert(GetTexturesNum() == 2);
	GameIO::Instance()->DrawTexture(
		Rectangle{ rect.x + static_cast<int>(rect.height * 0.05), rect.y + static_cast<int>(rect.height * 0.05), 
			static_cast<int>(rect.height * 0.9), static_cast<int>(rect.height * 0.9) },
		GetTexture(1));

	GameIO::Instance()->DrawLine(Vector2(rect.height + rect.x, rect.height * 0.25), Font::Treasures, text);
}

const Rectangle& ContentField::GetRect() const {
	return rect;
}