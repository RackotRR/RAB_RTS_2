#pragma once
#include <assert.h>
#include "TextureType.h"

class ProgressBar {
public:
	/// <summary>
	/// ���������� ������ ��� �������� � ����������� �� ��������� value � maxValue.
	/// ������� [0] - ��� �������� value == maxValue.
	/// �������� � ������� �������� value.
	/// </summary>
	/// <typeparam name="T">-�������� ��� ��������</typeparam>
	/// <param name="value">-������� ��������</param>
	/// <param name="maxValue">-������������ ��������</param>
	/// <param name="types">-���� ������� (������)</param> 
	template <unsigned int N, typename T>
	static TextureType GetTexture(T value, T maxValue, TextureType types[N]) {
		assert(N > 0);
		// ������� ������� 
		double quotient = static_cast<double>(value) / static_cast<double>(maxValue);
		unsigned int max = N - 1;
		// �������� �� ������������� ���������� �������� �� 0
		for (long i = max; i >= 0; i--) {
			double percent = static_cast<double>(i) / static_cast<double>(max);
			// ���� ���������� ������� ������ �����������, �� ��� �������� ��� �������
			if (percent <= quotient) return types[max - i];
			/*
			N = 5
			max = 4
			i = 4) 1.00 -> ret 0
			i = 3) 0.75 -> ret 1
			i = 2) 0.50 -> ret 2
			i = 1) 0.25 -> ret 3
			i = 0) 0.00 -> ret 4
			*/
		}
		// �������� ������ ���������� �� ����� �����
		assert("Something strange in progress bar: texture was not found!" && false);
		return TextureType::none;
	}
};