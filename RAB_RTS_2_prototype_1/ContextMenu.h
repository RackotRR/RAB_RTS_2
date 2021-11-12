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
	// �������� ���������� Y ������� ����� ���� 
	unsigned short menuTop;

	// �������� ���������� Y ������ ����� ����
	const unsigned short bottomWindow;

	// ������ ���� � ��������
	const unsigned short menuHeight;

	// ���������� ���������� �������
	const Vector2 contextObject;

	// ��������� ������
	// ����������� ��� �������������
	virtual void SendTask(uint8_t num) {};

	// �������� ������
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
	// �������� ������������ ����
	static constexpr uint16_t speed{ 6 * 128 };
 
	// ��������� ����
	ContextMenuState state;
};
 
 