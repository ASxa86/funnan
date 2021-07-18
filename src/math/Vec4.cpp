#include <funnan/math/Vec4.h>
#include <cmath>

using namespace funnan::math;

Vec4 Vec4::operator+(const Vec4& x) const
{
	return {this->x + x.x, this->y + x.y, this->z + x.z, this->w + x.w};
}

Vec4 Vec4::operator-(const Vec4& x) const
{
	return {this->x - x.x, this->y - x.y, this->z - x.z, this->w - x.w};
}

Vec4 Vec4::operator*(const Vec4& x) const
{
	return {this->x * x.x, this->y * x.y, this->z * x.z, this->w * x.w};
}

Vec4 Vec4::operator*(float x) const
{
	return {this->x * x, this->y * x, this->z * x, this->w * x};
}

Vec4 Vec4::operator/(const Vec4& x) const
{
	return {this->x / x.x, this->y / x.y, this->z / x.z, this->w / x.w};
}

Vec4 Vec4::operator/(float x) const
{
	return {this->x / x, this->y / x, this->z / x, this->w / x};
}

float Vec4::magnitude() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

Vec4 Vec4::unit() const
{
	const auto mag = this->magnitude();

	if(mag > 0.0f)
	{
		return {this->x / mag, this->y / mag, this->z / mag, this->w / mag};
	}

	return {0.0f, 0.0f};
}

float Vec4::dot(const Vec4& x) const
{
	const auto Vec4 = *this * x;
	return {Vec4.x + Vec4.y + Vec4.z + Vec4.w};
}
