#include <funnan/math/Mat4.h>
#include <cmath>

using namespace funnan::math;

Mat4 Mat4::Identity()
{
	// clang-format off
	const std::array<std::array<float, 4>, 4> matrix = {{
		{{1.0f, 0.0f, 0.0f, 0.0f}},
		{{0.0f, 1.0f, 0.0f, 0.0f}},
		{{0.0f, 0.0f, 1.0f, 0.0f}}, 
		{{0.0f, 0.0f, 0.0f, 1.0f}}
	}};
	// clang-format on

	return Mat4{matrix};
}

Mat4 Mat4::Translate(const Mat4& m, const Vec3& x)
{
	// https://learnopengl.com/Getting-started/Transformations
	auto translate = Mat4::Identity();
	translate.matrix[0][3] = x.x;
	translate.matrix[1][3] = x.y;
	translate.matrix[2][3] = x.z;
	return m * translate;
}

Mat4 Mat4::Scale(const Mat4& m, const Vec3& x)
{
	// https://learnopengl.com/Getting-started/Transformations
	auto scale = Mat4::Identity();
	scale.matrix[0][0] = x.x;
	scale.matrix[1][1] = x.y;
	scale.matrix[2][2] = x.z;
	return m * scale;
}

Mat4 Mat4::Rotate(const Mat4& m, float angle, const Vec3& x)
{
	// https://learnopengl.com/Getting-started/Transformations
	auto rotate = Mat4::Identity();
	const auto& rX = x.x;
	const auto& rY = x.y;
	const auto& rZ = x.z;

	const auto rX2 = x.x * x.x;
	const auto rY2 = x.y * x.y;
	const auto rZ2 = x.z * x.z;

	const auto rXY = rX * rY;
	const auto rXZ = rX * rZ;
	const auto rYZ = rY * rZ;
	const auto cos = std::cos(angle);
	const auto sin = std::sin(angle);

	const auto oneMinusCos = 1.0f - cos;
	const auto rXYOneMinusCos = rXY * oneMinusCos;
	const auto rXZOneMinusCos = rXZ * oneMinusCos;
	const auto rYZOneMinusCos = rYZ * oneMinusCos;
	const auto rXSin = rX * sin;
	const auto rYSin = rY * sin;
	const auto rZSin = rZ * sin;

	rotate.matrix[0][0] = cos + rX2 * oneMinusCos;
	rotate.matrix[0][1] = rXYOneMinusCos - rZSin;
	rotate.matrix[0][2] = rXZOneMinusCos + rYSin;

	rotate.matrix[1][0] = rXYOneMinusCos + rZSin;
	rotate.matrix[1][1] = cos + rY2 * oneMinusCos;
	rotate.matrix[1][2] = rYZOneMinusCos - rXSin;

	rotate.matrix[2][0] = rXZOneMinusCos - rYSin;
	rotate.matrix[2][1] = rYZOneMinusCos + rXSin;
	rotate.matrix[2][2] = cos + rZ2 * oneMinusCos;
	return m * rotate;
}

Mat4::Mat4(const std::array<std::array<float, 4>, 4>& x) : matrix{x}
{
}

Mat4 Mat4::operator*(const Mat4& x) const
{
	const auto& m11 = this->matrix[0][0];
	const auto& m12 = this->matrix[0][1];
	const auto& m13 = this->matrix[0][2];
	const auto& m14 = this->matrix[0][3];

	const auto& m21 = this->matrix[1][0];
	const auto& m22 = this->matrix[1][1];
	const auto& m23 = this->matrix[1][2];
	const auto& m24 = this->matrix[1][3];

	const auto& m31 = this->matrix[2][0];
	const auto& m32 = this->matrix[2][1];
	const auto& m33 = this->matrix[2][2];
	const auto& m34 = this->matrix[2][3];

	const auto& m41 = this->matrix[3][0];
	const auto& m42 = this->matrix[3][1];
	const auto& m43 = this->matrix[3][2];
	const auto& m44 = this->matrix[3][3];

	const auto& xm11 = x.matrix[0][0];
	const auto& xm12 = x.matrix[0][1];
	const auto& xm13 = x.matrix[0][2];
	const auto& xm14 = x.matrix[0][3];

	const auto& xm21 = x.matrix[1][0];
	const auto& xm22 = x.matrix[1][1];
	const auto& xm23 = x.matrix[1][2];
	const auto& xm24 = x.matrix[1][3];

	const auto& xm31 = x.matrix[2][0];
	const auto& xm32 = x.matrix[2][1];
	const auto& xm33 = x.matrix[2][2];
	const auto& xm34 = x.matrix[2][3];

	const auto& xm41 = x.matrix[3][0];
	const auto& xm42 = x.matrix[3][1];
	const auto& xm43 = x.matrix[3][2];
	const auto& xm44 = x.matrix[3][3];

	Mat4 mat{};
	mat.matrix[0][0] = m11 * xm11 + m12 * xm21 + m13 * xm31 + m14 * xm41;
	mat.matrix[0][1] = m11 * xm12 + m12 * xm22 + m13 * xm32 + m14 * xm42;
	mat.matrix[0][2] = m11 * xm13 + m12 * xm23 + m13 * xm33 + m14 * xm43;
	mat.matrix[0][3] = m11 * xm14 + m12 * xm24 + m13 * xm34 + m14 * xm44;

	mat.matrix[1][0] = m21 * xm11 + m22 * xm21 + m23 * xm31 + m24 * xm41;
	mat.matrix[1][1] = m21 * xm12 + m22 * xm22 + m23 * xm32 + m24 * xm42;
	mat.matrix[1][2] = m21 * xm13 + m22 * xm23 + m23 * xm33 + m24 * xm43;
	mat.matrix[1][3] = m21 * xm14 + m22 * xm24 + m23 * xm34 + m24 * xm44;

	mat.matrix[2][0] = m31 * xm11 + m32 * xm21 + m33 * xm31 + m34 * xm41;
	mat.matrix[2][1] = m31 * xm12 + m32 * xm22 + m33 * xm32 + m34 * xm42;
	mat.matrix[2][2] = m31 * xm13 + m32 * xm23 + m33 * xm33 + m34 * xm43;
	mat.matrix[2][3] = m31 * xm14 + m32 * xm24 + m33 * xm34 + m34 * xm44;

	mat.matrix[3][0] = m41 * xm11 + m42 * xm21 + m43 * xm31 + m44 * xm41;
	mat.matrix[3][1] = m41 * xm12 + m42 * xm22 + m43 * xm32 + m44 * xm42;
	mat.matrix[3][2] = m41 * xm13 + m42 * xm23 + m43 * xm33 + m44 * xm43;
	mat.matrix[3][3] = m41 * xm14 + m42 * xm24 + m43 * xm34 + m44 * xm44;

	return mat;
}

Vec4 Mat4::operator*(const Vec4& x) const
{
	const auto& m11 = this->matrix[0][0];
	const auto& m12 = this->matrix[0][1];
	const auto& m13 = this->matrix[0][2];
	const auto& m14 = this->matrix[0][3];

	const auto& m21 = this->matrix[1][0];
	const auto& m22 = this->matrix[1][1];
	const auto& m23 = this->matrix[1][2];
	const auto& m24 = this->matrix[1][3];

	const auto& m31 = this->matrix[2][0];
	const auto& m32 = this->matrix[2][1];
	const auto& m33 = this->matrix[2][2];
	const auto& m34 = this->matrix[2][3];

	const auto& m41 = this->matrix[3][0];
	const auto& m42 = this->matrix[3][1];
	const auto& m43 = this->matrix[3][2];
	const auto& m44 = this->matrix[3][3];

	const auto vx = m11 * x.x + m12 * x.y + m13 * x.z + m14 * x.w;
	const auto vy = m21 * x.x + m22 * x.y + m23 * x.z + m24 * x.w;
	const auto vz = m31 * x.x + m32 * x.y + m33 * x.z + m34 * x.w;
	const auto vw = m41 * x.x + m42 * x.y + m43 * x.z + m44 * x.w;
	return {vx, vy, vz, vw};
}
