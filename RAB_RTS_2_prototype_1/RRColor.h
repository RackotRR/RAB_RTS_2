#pragma once
/*
Абстракция цвета
*/
struct RRColor {
	RRColor() : r(0), g(0), b(0), a(255) {}
	RRColor(int r, int g, int b) : r(r), g(g), b(b), a(255) {}
	RRColor(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
	int r, g, b, a;
};