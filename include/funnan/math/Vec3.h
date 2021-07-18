#pragma once

#include <funnan/math/export.hxx>

namespace funnan
{
	namespace math
	{
		class FUNNAN_MATH_EXPORT Vec3 final
		{
		public:
			static constexpr auto SizeComponent{3};

			Vec3 operator+(const Vec3& x) const;
			Vec3 operator-(const Vec3& x) const;
			Vec3 operator*(const Vec3& x) const;
			Vec3 operator*(float x) const;
			Vec3 operator/(const Vec3& x) const;
			Vec3 operator/(float x) const;

			float magnitude() const;
			Vec3 unit() const;
			float dot(const Vec3& x) const;

			float x{};
			float y{};
			float z{};
		};
	}
}
