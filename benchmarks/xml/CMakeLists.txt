project(funnan-xml-benchmark)

add_executable(${PROJECT_NAME})

find_file(XMLTEST_FILE xmltest.xml PATHS ${CMAKE_SOURCE_DIR}/tests/xml/xmltest)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DXMLTEST_FILE="${XMLTEST_FILE}")

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	Parse.benchmark.cpp
)

find_package(celero CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	celero
	pugixml
	funnan-xml
)
