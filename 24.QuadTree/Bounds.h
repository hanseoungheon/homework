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
	//��ħ ���� �Լ�.
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

	//��ġ ������ ���� ���.
	float x = 0.0f;
	float y = 0.0f;

	float width = 1.0f;
	float height = 1.0f;
};