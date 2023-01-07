cmake_minimum_required(VERSION 3.23)

project(ascend)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/ascend/Factory.h
	${PROJECT_INCLUDE_DIR}/ascend/ReadBinary.h
	${PROJECT_INCLUDE_DIR}/ascend/ReadJSON.h
	${PROJECT_INCLUDE_DIR}/ascend/ReadXML.h
	${PROJECT_INCLUDE_DIR}/ascend/StringHash.h
	${PROJECT_INCLUDE_DIR}/ascend/WriteJSON.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Factory.cpp
	ReadBinary.cpp
	ReadJSON.cpp
	ReadXML.cpp
	WriteJSON.cpp
)

find_package(Qt6 CONFIG COMPONENTS Core)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt::Core
)

project_compile_options()
project_gen_export()
project_install_target()
