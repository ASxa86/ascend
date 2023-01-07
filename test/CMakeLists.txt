project(test-ascend)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	Factory.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	ascend
	GTest::gtest_main
	GTest::gtest
)

project_install_target()
project_compile_options()
