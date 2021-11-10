#include "ContextMenu.h"   
#include "GameIO.h"

ContextMenu::ContextMenu(const Vector2& contextObject, uint16_t windowHeight, uint16_t height) :
	contextObject{ contextObject },
	menuHeight{ height },
	bottomWindow{ windowHeight },
	menuTop{ windowHeight },
	state{ ContextMenuState::movingUp }
{
}

void ContextMenu::Hide() {
	state = ContextMenuState::movingDown;
}

bool ContextMenu::Update() {
	if (state == ContextMenuState::movingDown) { // закрываем меню
		menuTop += GetSpeed();
		if (menuTop > bottomWindow) { // если полностью закылось, то уничтожаем его
			state = ContextMenuState::closed;
			return true; // сообщаем об этом
		}
	}
	else if (state == ContextMenuState::movingUp) { // открываем меню
		menuTop -= GetSpeed();
		if (menuTop < bottomWindow - menuHeight) { // полностью открыто
			menuTop = bottomWindow - menuHeight;
			state = ContextMenuState::opened;
		}
	}
	return false;
}

uint16_t ContextMenu::GetSpeed() const {
	return static_cast<uint16_t>(speed * GameIO::Instance()->GetTicks());
}

const Vector2& ContextMenu::GetContextObject() const {
	return contextObject;
}


bool ContextMenu::ProcessInput(const RRMouse& mouseState) {
	for (int i = 0; i < buttons.size(); i++) {
		const Circle& circle = buttons[i].GetArea();
		// если нажали по кнопке
		if (circle.IsInCircle(Vector2{ mouseState.Position.X, mouseState.Position.Y - menuTop })) {
			SendTask(i);
			Hide();
			return true; // мы могли попасть только по одной кнопке. именно она и сработает
		}
	}
	return false;
}
 
void ContextMenu::AddButton(TextureType texture) {
	int radius = static_cast<int>(0.5 * menuHeight * 0.9);
	buttons.emplace_back( // в такой окружности будет круглая кнопка
		Circle(menuHeight + radius * (2 * static_cast<int>(buttons.size()) + 1), // X
			menuHeight - radius, // Y
			radius), // R.				
		RRTextureManager::Instance()->GetTexture(texture));  
}

void ContextMenu::GenerateOutput() { 
	for (auto& iter : buttons) { // проходим по кнопкам
		Rectangle rect = iter.GetArea();
		rect.y += menuTop; // координаты были относительно меню. Переводим в экранные
		GameIO::Instance()->DrawTexture(rect, iter.GetTexture()); // и рисуем их
	}
}