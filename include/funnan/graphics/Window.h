#pragma once

#include <Windows.h>
#include <funnan/Pimpl.H>
#include <funnan/graphics/Event.h>
#include <funnan/math/Vec2.h>
#include <functional>
#include <funnan/graphics/export.hxx>

namespace funnan
{
	namespace graphics
	{
		class FUNNAN_GRAPHICS_EXPORT Window final
		{
		public:
			Window(int width, int height);
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			bool getOpen() const;
			void close();
			void display();

			void processEvents();
			void addEvent(const Event& x);
			std::vector<Event> getEvents();

			funnan::math::Vec2 getPosition() const;
			funnan::math::Vec2 getSize() const;

			void addCallbackEventKeyboard(std::function<void(const EventKeyboard&)> x);
			void addCallbackEventMouse(std::function<void(const EventMouse&)> x);
			void addCallbackEventWindow(std::function<void(const EventWindow&)> x);

			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}