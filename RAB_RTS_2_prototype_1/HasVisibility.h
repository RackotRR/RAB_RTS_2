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
	1 - ��� 4 ������ ������ (����, ���, ����, �����)
	2 - ��� 12 ������ ������ � �.�.
	*/ 
	int visibility;
};

