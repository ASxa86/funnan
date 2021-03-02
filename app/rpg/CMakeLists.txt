project(rpg)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	funnan
)

project_install_target()
project_compile_options()
