project(funnan-graphics)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Bindable.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/BindGuard.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Event.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/EventKeyboard.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/EventMouse.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/EventWindow.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Geometry.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Program.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Shader.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Vertex.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/VertexBufferObject.h
	${PROJECT_INCLUDE_DIR}/funnan/graphics/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Bindable.cpp
	BindGuard.cpp
	Event.cpp
	Geometry.cpp
	glad.c
	Program.cpp
	Shader.cpp
	Vertex.cpp
	VertexBufferObject.cpp
	Window.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	opengl32
)

project_gen_export()
project_compile_options()
project_install_target()
