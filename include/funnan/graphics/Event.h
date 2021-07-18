#pragma once

#include <funnan/graphics/EventKeyboard.h>
#include <funnan/graphics/EventMouse.h>
#include <funnan/graphics/EventWindow.h>
#include <variant>

namespace funnan
{
	namespace graphics
	{
		using Event = std::variant<EventKeyboard, EventMouse, EventWindow>;
	}
}
