#include "ResourceContextMenu.h"
#include "ProgressBar.h" 

ResourceContextMenu::ResourceContextMenu(int height, const Vector2& contextObject, int maxValue, int value) :
	ContextMenu{ contextObject, GameIO::Instance()->GetWinHeight(), height },
	gameIO{ GameIO::Instance() },
	HPBar{ Rectangle{ 0, 0, height, height } }
{
	TextureType textures[6];
	textures[0] = TextureType::hpbar1;
	textures[1] = TextureType::hpbar2;
	textures[2] = TextureType::hpbar3;
	textures[3] = TextureType::hpbar4;
	textures[4] = TextureType::hpbar5;
	textures[5] = TextureType::hpbar6; 
	HPBar.AddTexture(RRTextureManager::Instance()->GetTexture(ProgressBar::GetTexture<6>(value, maxValue, textures)));
}

ResourceContextMenu::~ResourceContextMenu() {}
 
// вызвать для отрисовки  
void ResourceContextMenu::GenerateOutput() {
	DrawHPBar();
	ContextMenu::GenerateOutput();
}

void ResourceContextMenu::DrawHPBar() {
	gameIO->DrawTexture(
		Rectangle{ HPBar.GetArea().x, HPBar.GetArea().y + menuTop,
			HPBar.GetArea().width, HPBar.GetArea().height },
		HPBar.GetTexture());
}