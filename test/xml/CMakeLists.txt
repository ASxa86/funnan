project(funnan-xml-test)

add_executable(${PROJECT_NAME})

find_file(XMLTEST_FILE xmltest.xml PATHS ${CMAKE_SOURCE_DIR}/tests/xml/xmltest)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DXMLTEST_FILE="${XMLTEST_FILE}")

target_sources(${PROJECT_NAME} PRIVATE
	Document.test.cpp
	Element.test.cpp
	W3C.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	funnan-xml
	GTest::gtest_main
	GTest::gtest
)
