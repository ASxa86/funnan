project(funnan-xml-test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	Document.test.cpp
	Element.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	funnan-xml
	GTest::gtest_main
	GTest::gtest
)
