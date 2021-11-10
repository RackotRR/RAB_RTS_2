#include "Camera.h"
#include "GameIO.h"
 
Camera::Camera() :
	gameIO(GameIO::Instance()),
	dx(), dy(),
	vx(12), vy(12),
	cellSize(128)
{  
}

double Camera::GetVY() const {
	return vy * cellSize * gameIO->GetTicks();
}
double Camera::GetVX() const {
	return vx * cellSize * gameIO->GetTicks();
}
int Camera::GetDX() const {
	return static_cast<int>(dx);
}
int Camera::GetDY() const {
	return static_cast<int>(dy);
}
int Camera::GetCellSize() const {
	return cellSize;
}

void Camera::Update() {
	const RRMouse& mouseState = gameIO->GetMouseState();
	const KeyboardState& keyState = gameIO->GetKeyState();

	UpdateOffset(mouseState, keyState);
	  
	// сделать такую же штуку с колёсиком мыши
	if (keyState.IsKeyDown(Keys::Q))
		UpdateScale(cellSize - 1);
	if (keyState.IsKeyDown(Keys::E))
		UpdateScale(cellSize + 1); 
}

void Camera::UpdateOffset(const RRMouse& mouseState, const KeyboardState& keyState) {
	if (mouseState.Position.X >= gameIO->GetWinWidth() - 1 ||
		keyState.IsKeyDown(Keys::D)) {
		dx -= GetVX();
	}
	if (mouseState.Position.X <= 0 ||
		keyState.IsKeyDown(Keys::A)) {
		dx += GetVX();
	}
	if (mouseState.Position.Y >= gameIO->GetWinHeight() - 1 ||
		keyState.IsKeyDown(Keys::S)) {
		dy -= GetVY();
	}
	if (mouseState.Position.Y <= 0 ||
		keyState.IsKeyDown(Keys::W)) {
		dy += GetVY();
	}
}
 
void Camera::UpdateScale(int newSize) {
	// бессмысленное масштабирование
	if (newSize < 1 || newSize > gameIO->GetWinHeight() / 2)
		return;

	// считаем новое смещение экрана
	double ABSDX = gameIO->GetWinWidth() * 0.5 - dx;  // расстояние от (0, 0) до центра по ОХ
	dx += ABSDX * (1.0 - 1.0 * newSize / cellSize);

	double ABSDY = gameIO->GetWinHeight() * 0.5 - dy; // расстояние от (0, 0) до центра по ОY
	dy += ABSDY * (1.0 - 1.0 * newSize / cellSize);

	cellSize = newSize;
}