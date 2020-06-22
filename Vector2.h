#pragma once

class Vector2
{

private:

	float m_X;
	float m_Y;

public:

	Vector2() : m_X(0), m_Y(0) { }
	Vector2(float x, float y) : m_X(x), m_Y(y) { }
	Vector2(Vector2& vec) : m_X(vec.m_X), m_Y(vec.m_Y) { }

	inline float getX() { return m_X; }
	inline void setX(float x) { m_X = x; }

	inline float getY() { return m_Y; }
	inline void setY(float y) { m_Y = y; }

	Vector2& clear();
	Vector2& set(int x, int y);
	Vector2& set(float x, float y);
	Vector2& set(double x, double y);
	Vector2& set(Vector2& vec);

	Vector2& add(const Vector2& vec);
	Vector2& subtract(const Vector2& vec);
	Vector2& multiply(const Vector2& vec);
	Vector2& divide(const Vector2& vec);

	friend Vector2& operator + (Vector2& v1, const Vector2& v2);
	friend Vector2& operator - (Vector2& v1, const Vector2& v2);
	friend Vector2& operator * (Vector2& v1, const Vector2& v2);
	friend Vector2& operator / (Vector2& v1, const Vector2& v2);

	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (const Vector2& vec);
	Vector2& operator /= (const Vector2& vec);

};
