#include <funnan/math/Mat4.h>
#include <funnan/math/Math.h>
#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>

#include <funnan/graphics/Program.h>
#include <funnan/graphics/Shader.h>
#include <funnan/graphics/VertexBufferObject.h>
#include <funnan/graphics/Window.h>

using namespace funnan::math;
using namespace funnan::graphics;

constexpr std::string_view vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 position;

	void main()
	{
	   gl_Position = vec4(position.x, position.y, position.z, 1.0);
	}
)";

constexpr std::string_view fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
)";

int main()
{
	using seconds = std::chrono::duration<double>;
	std::vector<seconds> frames;
	frames.reserve(50'000'000);

	Window window(1280, 720);

	window.addCallbackEventWindow([&window](const EventWindow& e) {
		switch(e.type)
		{
			case EventWindow::Type::Closed:
				window.close();
				break;

			case EventWindow::Type::Resized:
				std::cout << "Resized: (" << e.width << ", " << e.height << ")" << std::endl;
				break;

			case EventWindow::Type::Moved:
				std::cout << "Moved: (" << e.x << ", " << e.y << ")" << std::endl;
				break;
		}
	});

	window.addCallbackEventMouse([](const EventMouse& e) {
		switch(e.type)
		{
			case EventMouse::Type::Moved:
				std::cout << "Moved (" << e.x << ", " << e.y << ")" << std::endl;
				break;

			case EventMouse::Type::WheelUp:
				std::cout << "Wheel Up" << std::endl;
				break;

			case EventMouse::Type::WheelDown:
				std::cout << "Wheel Down" << std::endl;
				break;

			case EventMouse::Type::WheelLeft:
				std::cout << "Wheel Left" << std::endl;
				break;

			case EventMouse::Type::WheelRight:
				std::cout << "Wheel Right" << std::endl;
				break;

			default:
				std::cout << "Mouse Event: " << static_cast<int>(e.type) << std::endl;
		}
	});

	window.addCallbackEventKeyboard([](const EventKeyboard& x) {
		switch(x.type)
		{
			case EventKeyboard::Type::KeyPressed:
				if(x.key == EventKeyboard::Key::A)
				{
					std::cout << "A" << std::endl;
				}
				break;
		}
	});

	Program program;
	Shader frag{Shader::Type::Fragment};
	frag.load(fragmentShaderSource);

	Shader vert{Shader::Type::Vertex};
	vert.load(vertexShaderSource);

	program.attach({vert, frag});
	program.allocateAttribute<funnan::math::Vec3>("position");
	program.allocateAttribute<funnan::math::Vec2>("textureCoords");
	program.allocateAttribute<funnan::math::Vec4>("color");

	std::vector<funnan::graphics::Vertex> vertices;
	vertices.push_back({0.5f, 0.5f, 0.0f});
	vertices.push_back({0.5f, -0.5f, 0.0f});
	vertices.push_back({-0.5f, -0.5f, 0.0f});
	vertices.push_back({-0.5f, 0.5f, 0.0f});

	std::array<unsigned int, 6> indices{
		0, 1, 3, // first Triangle
		1, 2, 3	 // second Triangle
	};

	VertexBufferObject vbo;
	vbo.load(vertices);

	unsigned int VAO, EBO;

	while(window.getOpen() == true)
	{
		const auto start = std::chrono::steady_clock::now();
		window.processEvents();

		// Draw

		window.display();

		seconds elapsed = std::chrono::steady_clock::now() - start;
		frames.push_back(elapsed);
	}

	const auto sum = std::accumulate(std::begin(frames), std::end(frames), seconds{});
	const auto avg = sum / frames.size();

	std::cout << "   Avg: " << std::setprecision(6) << std::fixed << 1.0 / avg.count() << std::endl;
	std::cout << "Frames: " << frames.size() << std::endl;

	return 0;
}
