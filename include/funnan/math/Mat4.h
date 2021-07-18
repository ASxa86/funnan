#pragma once

#include <funnan/math/Vec3.h>
#include <funnan/math/Vec4.h>
#include <array>
#include <funnan/math/export.hxx>

namespace funnan
{
	namespace math
	{
		class FUNNAN_MATH_EXPORT Mat4 final
		{
		public:
			static constexpr auto SizeComponent{4 * 4};

			explicit Mat4(const std::array<std::array<float, 4>, 4>& x = {});
			static Mat4 Identity();
			static Mat4 Translate(const Mat4& m, const Vec3& x);
			static Mat4 Scale(const Mat4& m, const Vec3& x);
			static Mat4 Rotate(const Mat4& m, float angle, const Vec3& x);

			Mat4 operator*(const Mat4& x) const;
			Vec4 operator*(const Vec4& x) const;

		private:
			std::array<std::array<float, 4>, 4> matrix{};
		};
	}
}