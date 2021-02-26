project(funnan-string)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/funnan/string/StringTo.h
	${PROJECT_INCLUDE_DIR}/funnan/string/ToString.h
	${PROJECT_INCLUDE_DIR}/funnan/string/TypeTraits.h
)

target_sources(${PROJECT_NAME} PRIVATE
	StringTo.cpp
	ToString.cpp
)

project_install_target()
project_compile_options()
project_gen_export()
