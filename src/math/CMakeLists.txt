project(funnan-math)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/funnan/math/Mat4.h
	${PROJECT_INCLUDE_DIR}/funnan/math/Math.h
	${PROJECT_INCLUDE_DIR}/funnan/math/Vec2.h
	${PROJECT_INCLUDE_DIR}/funnan/math/Vec3.h
	${PROJECT_INCLUDE_DIR}/funnan/math/Vec4.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Mat4.cpp
	Math.cpp
	Vec2.cpp
	Vec3.cpp
	Vec4.cpp
)

project_gen_export()
project_compile_options()
project_install_target()
