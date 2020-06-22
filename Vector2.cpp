#include "Vector2.h"

Vector2& Vector2::clear()
{
	m_X = 0;
	m_Y = 0;

	return *this;
}

Vector2& Vector2::set(int x, int y)
{
	m_X = (float) x;
	m_Y = (float) y;

	return *this;
}

Vector2& Vector2::set(float x, float y)
{
	m_X = x;
	m_Y = y;

	return *this;
}

Vector2& Vector2::set(double x, double y)
{
	m_X = (float) x;
	m_Y = (float) y;

	return *this;
}

Vector2& Vector2::set(Vector2& vec)
{
	m_X = vec.m_X;
	m_Y = vec.m_Y;

	return *this;
}

Vector2& Vector2::add(const Vector2& vec)
{
	m_X += vec.m_X;
	m_Y += vec.m_Y;

	return *this;
}

Vector2& Vector2::subtract(const Vector2& vec)
{
	m_X -= vec.m_X;
	m_Y -= vec.m_Y;

	return *this;
}

Vector2& Vector2::multiply(const Vector2& vec)
{
	m_X *= vec.m_X;
	m_Y *= vec.m_Y;

	return *this;
}

Vector2& Vector2::divide(const Vector2& vec)
{
	m_X /= vec.m_X;
	m_Y /= vec.m_Y;

	return *this;
}

Vector2& operator+(Vector2& v1, const Vector2& v2)
{
	return v1.add(v2);
}

Vector2& operator-(Vector2& v1, const Vector2& v2)
{
	return v1.subtract(v2);
}

Vector2& operator*(Vector2& v1, const Vector2& v2)
{
	return v1.multiply(v2);
}

Vector2& operator/(Vector2& v1, const Vector2& v2)
{
	return v1.divide(v2);
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	return this->add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	return this->subtract(vec);
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	return this->multiply(vec);
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	return this->divide(vec);
}
