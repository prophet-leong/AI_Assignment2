#include <cmath>
#include "Vector2.h"

Vector2::Vector2(float a, float b) : x(a), y(b)
{

}

Vector2::Vector2(const Vector2 &rhs)
{
	x = rhs.x;
	y = rhs.y;
}

void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2::operator=(const Vector2&rhs) 
{
	x = rhs.x;
	y = rhs.y;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-(void) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(scalar * x, scalar * y);
}

float Vector2::Length(void) const
{
	return sqrt(x * x + y * y);
}

float Vector2::LengthSquare(void)const
{
	return  x * x + y * y;
}

float Vector2::Dot(const Vector2& rhs) const
{
	return ((x* rhs.x) + (y * rhs.y));
}


bool Vector2::operator==(const Vector2&rhs) const
{
	return(x == rhs.x && y == rhs.y);
}
 
bool Vector2::operator!=(const Vector2&rhs) const
{
	return !( *this == rhs);
}

Vector2 Vector2::operator+=(const Vector2&rhs) const
{
	return Vector2(x+rhs.x,y+rhs.y);
}
Vector2 Vector2::Normalized()
{
	float d = Length();
	if (d != 0.000f)
		return Vector2(x / d, y / d);
	else
		return Vector2(0.0f,0.0f);
}
std::ostream& operator<< (std::ostream& os, Vector2& rhs)
{
	os << "[ " << rhs.x << ", " << rhs.y << " ]";
	return os;
}


