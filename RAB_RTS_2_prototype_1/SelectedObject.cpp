#include "SelectedObject.h"

SelectedObject::SelectedObject(World* world) :
	position(Vector2::WrongPosition),
	type(ObjectType::none),
	selected(false),
	world(world)
{}

ObjectType SelectedObject::Select(const Vector2& v) {
	ObjectType type = world->CheckPosition(v); // проверяем, что по этим координатам
	this->type = type;
	if (type == ObjectType::none || type == ObjectType::ground) {
		selected = false; // если кликнули по пустому месту, то снять выделение
	}
	else { // если что-то выбрали 
		position = v;
		selected = true;
	}
	return type;
}


bool SelectedObject::IsSmthSelected() const {
	return selected;
}

void SelectedObject::SelectNothing() {
	selected = false;
	position = Vector2::WrongPosition;
	type = ObjectType::none;
}

const Vector2& SelectedObject::GetPosition() const {
	return position;
}

ObjectType SelectedObject::GetType() const {
	return type;
}