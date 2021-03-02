project(test-funnan)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	physics/SystemPhysics.test.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
	ComponentFactory.test.cpp
	ComponentPool.test.cpp
	Entity.test.cpp
	Scene.test.cpp
	SceneParser.test.cpp
	Time.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	funnan
	GTest::gtest_main
	GTest::gtest
)

if(MSVC)
	source_group("Source Files/physics" REGULAR_EXPRESSION "physics/*")
endif()

project_install_target()
project_compile_options()
