#include <funnan/math/Vec3.h>
#include <cmath>

using namespace funnan::math;

Vec3 Vec3::operator+(const Vec3& x) const
{
	return {this->x + x.x, this->y + x.y, this->z + x.z};
}

Vec3 Vec3::operator-(const Vec3& x) const
{
	return {this->x - x.x, this->y - x.y, this->z - x.z};
}

Vec3 Vec3::operator*(const Vec3& x) const
{
	return {this->x * x.x, this->y * x.y, this->z * x.z};
}

Vec3 Vec3::operator*(float x) const
{
	return {this->x * x, this->y * x, this->z * x};
}

Vec3 Vec3::operator/(const Vec3& x) const
{
	return {this->x / x.x, this->y / x.y, this->z / x.z};
}

Vec3 Vec3::operator/(float x) const
{
	return {this->x / x, this->y / x, this->z / x};
}

float Vec3::magnitude() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vec3 Vec3::unit() const
{
	const auto mag = this->magnitude();

	if(mag > 0.0f)
	{
		return {this->x / mag, this->y / mag, this->z / mag};
	}

	return {0.0f, 0.0f};
}

float Vec3::dot(const Vec3& x) const
{
	const auto vec3 = *this * x;
	return {vec3.x + vec3.y + vec3.z};
}
