#include "Color.h"

Color::Color()
{

}
Color::Color(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
Color Color::operator = (Color &other)
{
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	return *this;
};