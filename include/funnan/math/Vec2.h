#pragma once

#include <funnan/math/export.hxx>

namespace funnan
{
	namespace math
	{
		class FUNNAN_MATH_EXPORT Vec2 final
		{
		public:
			static constexpr auto SizeComponent{2};

			Vec2 operator+(const Vec2& x) const;
			Vec2 operator-(const Vec2& x) const;
			Vec2 operator*(const Vec2& x) const;
			Vec2 operator*(float x) const;
			Vec2 operator/(const Vec2& x) const;
			Vec2 operator/(float x) const;

			float magnitude() const;
			Vec2 unit() const;
			float dot(const Vec2& x) const;

			float x{};
			float y{};
		};
	}
}