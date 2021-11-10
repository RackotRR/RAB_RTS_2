#include "Resource.h"
#include <assert.h>

Resource::Resource(const Vector2& position, int value, int maxValue, ResourceType type)
	: Actor(position), value(value), maxValue(maxValue), type(type), HasTexture() {}

ResourceType Resource::GetType() const {
	return type;
}

int Resource::Take(int val) {
	assert(val >= 0);

	value -= val;

	if (value < 0)
		return val - value;
	else
		return val;
}


bool Resource::IsOver() const {
	return (value <= 0);
}

int Resource::GetValue() const {
	return value;
}
int Resource::GetMaxValue() const {
	return maxValue;
}