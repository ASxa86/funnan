project(funnan)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/funnan/ComponentFactory.h
	${PROJECT_INCLUDE_DIR}/funnan/ComponentPool.h
	${PROJECT_INCLUDE_DIR}/funnan/ComponentTransform.h
	${PROJECT_INCLUDE_DIR}/funnan/Entity.h
	${PROJECT_INCLUDE_DIR}/funnan/EntityID.h
	${PROJECT_INCLUDE_DIR}/funnan/Properties.h
	${PROJECT_INCLUDE_DIR}/funnan/Property.h
	${PROJECT_INCLUDE_DIR}/funnan/PropertyTemplateMember.h
	${PROJECT_INCLUDE_DIR}/funnan/PropertyTemplateMethod.h
	${PROJECT_INCLUDE_DIR}/funnan/Scene.h
	${PROJECT_INCLUDE_DIR}/funnan/SceneParser.h
	${PROJECT_INCLUDE_DIR}/funnan/Signal.h
	${PROJECT_INCLUDE_DIR}/funnan/System.h
	${PROJECT_INCLUDE_DIR}/funnan/TypeInfo.h
	${PROJECT_INCLUDE_DIR}/funnan/Time.h
	${PROJECT_INCLUDE_DIR}/funnan/Size.h
	${PROJECT_INCLUDE_DIR}/funnan/Vector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/funnan/physics/ComponentBody.h
	${PROJECT_INCLUDE_DIR}/funnan/physics/Fixture.h
	${PROJECT_INCLUDE_DIR}/funnan/physics/SystemPhysics.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComponentFactory.cpp
	Entity.cpp
	Properties.cpp
	Property.cpp
	Scene.cpp
	SceneParser.cpp
	System.cpp
	TypeInfo.cpp
	Time.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
	physics/ComponentBody.cpp
	physics/Fixture.cpp
	physics/SystemPhysics.cpp
)

find_package(Boost REQUIRED COMPONENTS system)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(unofficial-box2d CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
	nlohmann_json
	nlohmann_json::nlohmann_json
	pugixml
	unofficial::box2d::box2d
)

if(MSVC)
	source_group("Header Files/physics" REGULAR_EXPRESSION "${PROJECT_INCLUDE_DIR}/funnan/physics/*")
	source_group("Source Files/physics" REGULAR_EXPRESSION "physics/*")
endif()

project_install_target()
project_compile_options()
project_gen_export()
