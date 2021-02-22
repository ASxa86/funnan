project(funnan-xml)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/funnan/xml/Attribute.h
	${PROJECT_INCLUDE_DIR}/funnan/xml/Document.h
	${PROJECT_INCLUDE_DIR}/funnan/xml/Element.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Attribute.cpp
	Document.cpp
	Element.cpp
)

project_install_target()
project_compile_options()
project_gen_export()
