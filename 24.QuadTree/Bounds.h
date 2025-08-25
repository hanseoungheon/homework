#pragma once

struct Position
{

};
class Bounds
{
public:

	Bounds()
	{

	}
	Bounds(float x, float y, float width = 1.0f, float height = 1.0f)
		: x(x), y(y), width(width), height(height)
	{

	}
	//겹침 판정 함수.
	bool Intersects(const Bounds& other) const;

public:
	//Getter & Setter
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	float MaxX() const { return x + width; }
	float MaxY() const { return y + height; }
	float CenterX() const { return (x + width) / 2; }

private:

	//위치 기준은 왼쪽 상단.
	float x = 0.0f;
	float y = 0.0f;

	float width = 1.0f;
	float height = 1.0f;
};