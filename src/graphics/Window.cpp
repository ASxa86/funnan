#include <funnan/graphics/Window.h>

#include <funnan/PimplImpl.h>
#include <windowsx.h>
#include <algorithm>

using namespace funnan::graphics;

bool active;

// clang-format off
EventKeyboard::Key MapKey(WPARAM key)
{
	switch(key)
	{
		case 'A': return EventKeyboard::Key::A;
		case 'B': return EventKeyboard::Key::B;
		case 'C': return EventKeyboard::Key::C;
		case 'D': return EventKeyboard::Key::D;
		case 'E': return EventKeyboard::Key::E;
		case 'F': return EventKeyboard::Key::F;
		case 'G': return EventKeyboard::Key::G;
		case 'H': return EventKeyboard::Key::H;
		case 'I': return EventKeyboard::Key::I;
		case 'J': return EventKeyboard::Key::J;
		case 'K': return EventKeyboard::Key::K;
		case 'L': return EventKeyboard::Key::L;
		case 'M': return EventKeyboard::Key::M;
		case 'N': return EventKeyboard::Key::N;
		case 'O': return EventKeyboard::Key::O;
		case 'P': return EventKeyboard::Key::P;
		case 'Q': return EventKeyboard::Key::Q;
		case 'R': return EventKeyboard::Key::R;
		case 'S': return EventKeyboard::Key::S;
		case 'T': return EventKeyboard::Key::T;
		case 'U': return EventKeyboard::Key::U;
		case 'V': return EventKeyboard::Key::V;
		case 'W': return EventKeyboard::Key::W;
		case 'X': return EventKeyboard::Key::X;
		case 'Y': return EventKeyboard::Key::Y;
		case 'Z': return EventKeyboard::Key::Z;
	}

	return EventKeyboard::Key::Unknown;
}
// clang-format on

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const auto longPtr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	auto window = reinterpret_cast<Window*>(longPtr);

	if(window != nullptr)
	{
		switch(uMsg) // Check For Windows Messages
		{
			case WM_ACTIVATE: // Watch For Window Activate Message
			{
				if(!HIWORD(wParam)) // Check Minimization State
				{
					active = TRUE; // Program Is Active
				}
				else
				{
					active = FALSE; // Program Is No Longer Active
				}

				return 0; // Return To The Message Loop
			}
			case WM_SYSCOMMAND: // Intercept System Commands
			{
				switch(wParam) // Check System Calls
				{
					case SC_SCREENSAVE:	  // Screensaver Trying To Start?
					case SC_MONITORPOWER: // Monitor Trying To Enter Powersave?
						return 0;		  // Prevent From Happening
				}
				break; // Exit
			}
			case WM_CLOSE: // Did We Receive A Close Message?
			{
				EventWindow event;
				event.type = EventWindow::Type::Closed;
				window->addEvent(event);

				return 0; // Jump Back
			}
			case WM_KEYDOWN: // Is A Key Being Held Down?
			{
				EventKeyboard event;
				event.type = EventKeyboard::Type::KeyPressed;
				event.key = MapKey(wParam);
				window->addEvent(event);

				return 0; // Jump Back
			}
			case WM_KEYUP: // Has A Key Been Released?
			{
				EventKeyboard event;
				event.type = EventKeyboard::Type::KeyReleased;
				event.key = MapKey(wParam);
				window->addEvent(event);
				return 0; // Jump Back
			}
			case WM_MOUSEWHEEL:
			{
				EventMouse event;
				const auto delta = GET_WHEEL_DELTA_WPARAM(wParam);

				if(delta > 0)
				{
					event.type = EventMouse::Type::WheelUp;
				}
				else if(delta < 0)
				{
					event.type = EventMouse::Type::WheelDown;
				}

				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);

				return 0;
			}

			case WM_MOUSEHWHEEL:
			{
				EventMouse event;
				const auto delta = GET_WHEEL_DELTA_WPARAM(wParam);

				if(delta > 0)
				{
					event.type = EventMouse::Type::WheelRight;
				}
				else if(delta < 0)
				{
					event.type = EventMouse::Type::WheelLeft;
				}

				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);

				return 0;
			}

			// Mouse left button down event
			case WM_LBUTTONDOWN:
			{
				EventMouse event;
				event.type = EventMouse::Type::ButtonLeftPressed;
				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);
				return 0;
			}

			// Mouse left button up event
			case WM_LBUTTONUP:
			{
				EventMouse event;
				event.type = EventMouse::Type::ButtonLeftReleased;
				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);
				return 0;
			}

			// Mouse right button down event
			case WM_RBUTTONDOWN:
			{
				EventMouse event;
				event.type = EventMouse::Type::ButtonRightPressed;
				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);
				return 0;
			}

			// Mouse right button up event
			case WM_RBUTTONUP:
			{
				EventMouse event;
				event.type = EventMouse::Type::ButtonRightReleased;
				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);
				return 0;
			}

			// Mouse wheel button down event
			case WM_MBUTTONDOWN:
			{
				EventMouse event;
				event.type = EventMouse::Type::ButtonMiddlePressed;
				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);
				return 0;
			}

			// Mouse wheel button up event
			case WM_MBUTTONUP:
			{
				EventMouse event;
				event.type = EventMouse::Type::ButtonMiddleReleased;
				event.x = GET_X_LPARAM(lParam);
				event.y = GET_Y_LPARAM(lParam);
				window->addEvent(event);
				return 0;
			}

			case WM_MOUSEMOVE:
			{
				// CTRL
				if((wParam & MK_CONTROL) != 0x0)
				{
				}

				if((wParam & MK_LBUTTON) != 0x0)
				{
				}

				if((wParam & MK_RBUTTON) != 0x0)
				{
				}

				if((wParam & MK_SHIFT) != 0x0)
				{
				}

				// https://stackoverflow.com/questions/9205534/win32-mouse-and-keyboard-combination
				if((HIBYTE(GetKeyState(VK_MENU)) & 0x80) != 0x0)
				{
				}

				const auto x = GET_X_LPARAM(lParam);
				const auto y = GET_Y_LPARAM(lParam);

				EventMouse event;
				event.type = EventMouse::Type::Moved;
				event.x = x;
				event.y = y;
				window->addEvent(event);

				return 0;
			}
			case WM_INPUT:
			{
				return 0;
			}
			case WM_SIZE:
			{
				return 0;
			}

			// Start resizing
			case WM_ENTERSIZEMOVE:
			{
				return 0;
			}

			// Stop resizing
			case WM_EXITSIZEMOVE:
			{
				EventWindow event;
				event.type = EventWindow::Type::Resized;
				event.width = window->getSize().x;
				event.height = window->getSize().y;
				window->addEvent(event);

				event.type = EventWindow::Type::Moved;
				event.x = window->getPosition().x;
				event.y = window->getPosition().y;
				window->addEvent(event);

				return 0;
			}

			default:
				break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

struct Window::Impl
{
	Impl(Window* window, int width, int height)
	{
		// https://docs.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
		this->hInstance = GetModuleHandle(nullptr);
		this->wc.lpfnWndProc = WndProc;
		this->wc.hInstance = this->hInstance;
		this->wc.lpszClassName = ClassName.data();

		RegisterClass(&this->wc);

		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;

		this->hWnd =
			CreateWindowEx(dwExStyle, Impl::ClassName.data(), "funnan", dwStyle, 0, 0, width, height, nullptr, nullptr, this->hInstance, nullptr);

		SetWindowLongPtr(this->hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}

	~Impl()
	{
		this->close();
	}

	void close()
	{
		wglDeleteContext(this->context);
		DestroyWindow(this->hWnd);
		UnregisterClassA(ClassName.data(), this->hInstance);
		this->open = false;
	}

	static constexpr std::string_view ClassName{"OpenGL"};

	std::vector<std::function<void(const EventKeyboard&)>> callbacksEventKeyboard;
	std::vector<std::function<void(const EventMouse&)>> callbacksEventMouse;
	std::vector<std::function<void(const EventWindow&)>> callbacksEventWindow;
	std::vector<Event> events;
	HMODULE hInstance{};
	WNDCLASS wc{};
	HWND hWnd{};
	HDC hDC{};
	HGLRC context{};
	bool open{false};
};

Window::Window(int width, int height) : pimpl(this, width, height)
{
	auto error = GetLastError();

	this->pimpl->hDC = GetDC(this->pimpl->hWnd);

	constexpr auto bits = 32;

	PIXELFORMATDESCRIPTOR pfd = // pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
			1,							   // Version Number
			PFD_DRAW_TO_WINDOW |		   // Format Must Support Window
				PFD_SUPPORT_OPENGL |	   // Format Must Support OpenGL
				PFD_DOUBLEBUFFER,		   // Must Support Double Buffering
			PFD_TYPE_RGBA,				   // Request An RGBA Format
			bits,						   // Select Our Color Depth
			0,
			0,
			0,
			0,
			0,
			0, // Color Bits Ignored
			0, // No Alpha Buffer
			0, // Shift Bit Ignored
			0, // No Accumulation Buffer
			0,
			0,
			0,
			0,				// Accumulation Bits Ignored
			16,				// 16Bit Z-Buffer (Depth Buffer)
			0,				// No Stencil Buffer
			0,				// No Auxiliary Buffer
			PFD_MAIN_PLANE, // Main Drawing Layer
			0,				// Reserved
			0,
			0,
			0 // Layer Masks Ignored
		};

	auto format = ChoosePixelFormat(this->pimpl->hDC, &pfd);
	SetPixelFormat(this->pimpl->hDC, format, &pfd);

	this->pimpl->context = wglCreateContext(this->pimpl->hDC);
	wglMakeCurrent(this->pimpl->hDC, this->pimpl->context);

	ShowWindow(this->pimpl->hWnd, SW_SHOW);
	SetForegroundWindow(this->pimpl->hWnd);
	SetFocus(this->pimpl->hWnd);
	ShowCursor(TRUE);

	this->pimpl->open = this->pimpl->hWnd != nullptr;
}

Window::~Window()
{
}

bool Window::getOpen() const
{
	return this->pimpl->open;
}

void Window::close()
{
	this->pimpl->close();
}

void Window::display()
{
	SwapBuffers(this->pimpl->hDC);
}

void Window::processEvents()
{
	const auto events = this->getEvents();

	for(const auto& event : events)
	{
		if(auto e = std::get_if<EventMouse>(&event))
		{
			for(const auto& f : this->pimpl->callbacksEventMouse)
			{
				f(*e);
			}
		}
		else if(auto e = std::get_if<EventKeyboard>(&event))
		{
			for(const auto& f : this->pimpl->callbacksEventKeyboard)
			{
				f(*e);
			}
		}
		else if(auto e = std::get_if<EventWindow>(&event))
		{
			for(const auto& f : this->pimpl->callbacksEventWindow)
			{
				f(*e);
			}
		}
	}
}

void Window::addEvent(const Event& x)
{
	this->pimpl->events.push_back(x);
}

std::vector<Event> Window::getEvents()
{
	std::vector<Event> v;

	if(this->getOpen() == true)
	{
		v.reserve(this->pimpl->events.size());

		MSG msg{};
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		std::swap(v, this->pimpl->events);
	}

	return v;
}

funnan::math::Vec2 Window::getPosition() const
{
	RECT rect;
	GetClientRect(this->pimpl->hWnd, &rect);

	return {static_cast<float>(rect.left), static_cast<float>(rect.top)};
}

funnan::math::Vec2 Window::getSize() const
{
	RECT rect;
	GetClientRect(this->pimpl->hWnd, &rect);

	return {static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top)};
}

void Window::addCallbackEventKeyboard(std::function<void(const EventKeyboard&)> x)
{
	this->pimpl->callbacksEventKeyboard.push_back(std::move(x));
}

void Window::addCallbackEventMouse(std::function<void(const EventMouse&)> x)
{
	this->pimpl->callbacksEventMouse.push_back(std::move(x));
}

void Window::addCallbackEventWindow(std::function<void(const EventWindow&)> x)
{
	this->pimpl->callbacksEventWindow.push_back(std::move(x));
}
