#pragma once

#include <funnan/math/Vec2.h>
#include <funnan/math/Vec3.h>
#include <funnan/math/Vec4.h>

namespace funnan
{
	namespace graphics
	{
		class Vertex
		{
		public:
			using TypePosition = funnan::math::Vec3;
			using TypeColor = funnan::math::Vec4;
			using TypeTextureCoords = funnan::math::Vec2;

			static constexpr auto AttribIndexPosition{0};
			static constexpr auto AttribIndexColor{1};
			static constexpr auto AttribIndexTextureCoords{2};

			static constexpr auto AttribComponentPosition{TypePosition::SizeComponent};
			static constexpr auto AttribComponentColor{TypeColor::SizeComponent};
			static constexpr auto AttribComponentTextureCoords{TypeTextureCoords::SizeComponent};

			TypePosition position{};
			TypeColor color{};
			TypeTextureCoords textureCoords{};
		};
	}
}
