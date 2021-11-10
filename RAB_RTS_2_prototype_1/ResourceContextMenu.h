#pragma once
#include "ContextMenu.h"


class ResourceContextMenu : public ContextMenu {
public:
	ResourceContextMenu(int height, const Vector2& contextObject, int maxValue, int value);
	virtual ~ResourceContextMenu();
	 
	// ������� ��� ���������  
	virtual void GenerateOutput();

protected:
	void DrawHPBar();
	GameIO* gameIO;
private: 
	ContextMenuItem<Rectangle> HPBar;
};
 