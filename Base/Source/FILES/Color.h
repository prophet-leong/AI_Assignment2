#pragma once
struct Color
{
	Color();
	Color(float r, float g, float b);
	float r;
	float g;
	float b;
	
	Color operator = (Color &other);
	void Set(float r, float g, float b){ r = r; g = g; b = b; }
};