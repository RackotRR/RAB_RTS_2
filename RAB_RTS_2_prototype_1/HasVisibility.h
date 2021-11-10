#pragma once
class HasVisibility
{
public:
	int GetVisibility() const {
		return visibility;
	} 
	void SetVisibility(int val) {
		visibility = val;
	}
private:
	/*
	1 - это 4 клетки вокруг (верх, низ, лево, право)
	2 - это 12 клеток вокруг и т.д.
	*/ 
	int visibility;
};

