#pragma once
#include <string>
using namespace std;

struct MyVector
{
	float x, y;
	MyVector() :x(0), y(0) {}
	MyVector(float x, float y) :x(x), y(y) {}
	void SetPosition(float _x, float _y) { x = _x; y = _y; }
	float GetX() { return x; }
	float GetY() { return y; }
	float Magnitude() { return sqrt(x*x + y*y); }
	MyVector Normalize() { float length = Magnitude(); return MyVector(x / length, y / length); }
	MyVector operator + (MyVector u) { return MyVector(x + u.x, y + u.y); }
	MyVector operator - (MyVector u) { return MyVector(u.x - x, u.y - y); }
	MyVector operator += (MyVector u) { return MyVector(x + u.x, y + u.y); }
	MyVector operator ~() { return MyVector(-x, -y); }
	MyVector operator *(float scale) { return MyVector(x*scale, y*scale); }
	float operator * (MyVector  v) { return  x*v.x + y*v.y; }
};

class genericEnemy
{
public:
	genericEnemy();
	~genericEnemy();

	void Init(MyVector pos, string name, int hp);
	void Update();
	float GetDistance(float x1, float y1, float x2, float y2) { return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)); } // OK
	bool checkPlayer(MyVector playerPos, float radius1, float radius2);

	int state;
	MyVector pos;
	int health;
	string name;
};