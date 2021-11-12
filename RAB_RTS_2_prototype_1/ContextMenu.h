#pragma once 
#include <cassert>
#include <vector>
#include <stdint.h>

#include "ContextMenuItem.h" 
#include "RRTextureManager.h"
#include "GameIO.h" 
#include "Circle.h"

class ContextMenu {
public:
	ContextMenu(const Vector2& contextObject, uint16_t windowHeight, uint16_t height);
	virtual ~ContextMenu() {}

	void Hide();

	virtual bool ProcessInput(const RRMouse& mouseState);

	bool Update();

	virtual void GenerateOutput();

	const Vector2& GetContextObject() const; 
protected:
	// экранная координата Y верхней части меню 
	unsigned short menuTop;

	// экранная координата Y нижней части окна
	const unsigned short bottomWindow;

	// высота меню в пикселях
	const unsigned short menuHeight;

	// координата выбранного объекта
	const Vector2 contextObject;

	// отправить задачу
	// перегрузить для использования
	virtual void SendTask(uint8_t num) {};

	// добавить кнопку
	void AddButton(TextureType texture); 
	std::vector<ContextMenuItem<Circle>> buttons;
private:
	enum class ContextMenuState {
		opened,
		closed,
		movingUp,
		movingDown
	};

	uint16_t GetSpeed() const;
	// скорость передвижения меню
	static constexpr uint16_t speed{ 6 * 128 };
 
	// состояние меню
	ContextMenuState state;
};
 
 