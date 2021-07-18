#pragma once

#include <funnan/math/export.hxx>

namespace funnan
{
	namespace math
	{
		class FUNNAN_MATH_EXPORT Vec4 final
		{
		public:
			static constexpr auto SizeComponent{4};

			Vec4 operator+(const Vec4& x) const;
			Vec4 operator-(const Vec4& x) const;
			Vec4 operator*(const Vec4& x) const;
			Vec4 operator*(float x) const;
			Vec4 operator/(const Vec4& x) const;
			Vec4 operator/(float x) const;

			float magnitude() const;
			Vec4 unit() const;
			float dot(const Vec4& x) const;

			union
			{
				float x{};
				float r;
			};

			union
			{
				float y{};
				float g;
			};

			union
			{
				float z{};
				float b;
			};

			union
			{
				float w{};
				float a;
			};
		};
	}
}
