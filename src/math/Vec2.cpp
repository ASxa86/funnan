#include <funnan/math/Vec2.h>
#include <cmath>

using namespace funnan::math;

Vec2 Vec2::operator+(const Vec2& x) const
{
	return {this->x + x.x, this->y + x.y};
}

Vec2 Vec2::operator-(const Vec2& x) const
{
	return {this->x - x.x, this->y - x.y};
}

Vec2 Vec2::operator*(const Vec2& x) const
{
	return {this->x * x.x, this->y * x.y};
}

Vec2 Vec2::operator*(float x) const
{
	return {this->x * x, this->y * x};
}

Vec2 Vec2::operator/(const Vec2& x) const
{
	return {this->x / x.x, this->y / x.y};
}

Vec2 Vec2::operator/(float x) const
{
	return {this->x / x, this->y / x};
}

float Vec2::magnitude() const
{
	return std::sqrt(this->x * this->x + this->y * this->y);
}

Vec2 Vec2::unit() const
{
	const auto mag = this->magnitude();

	if(mag > 0.0f)
	{
		return {this->x / mag, this->y / mag};
	}

	return {0.0f, 0.0f};
}

float Vec2::dot(const Vec2& x) const
{
	const auto vec2 = *this * x;
	return {vec2.x + vec2.y};
}
