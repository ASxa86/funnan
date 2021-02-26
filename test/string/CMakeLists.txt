project(funnan-string-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	StringTo.test.cpp
	ToString.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	funnan-string
	GTest::gtest_main
	GTest::gtest
)
