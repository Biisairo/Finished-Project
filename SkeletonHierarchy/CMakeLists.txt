# cmake version
cmake_minimum_required(VERSION 3.27)

# set variable
set(PROJECT_NAME skeleton_hierarchy)
set(CMAKE_CXX_STANDARD 11)

set(GLFW_USE 1)
set(GLAD_USE 1)
set(GLM_USE 1)
set(STB_IMAGE_USE 1)
set(ASSIMP_USE 0)
set(SPDLOG_USE 0)
set(IMGUI_USE 0)

# set project
project(
	${PROJECT_NAME}
	LANGUAGES CXX
)

# set source code
# put manual
# set(SOURCE_CODE ${SOURCE_CODE}
#     ./src/main.cpp
# )

# wild card
file(GLOB_RECURSE SOURCE_CODE
    ./src/**.cpp
)

# start build
add_executable(${PROJECT_NAME} ${SOURCE_CODE})

# dependency import
include(Dependency.cmake)

# set define
target_compile_definitions(${PROJECT_NAME} PUBLIC
GLFW_USE=${GLFW_USE}
GLAD_USE=${GLAD_USE}
GLM_USE=${GLM_USE}
STB_IMAGE_USE=${STB_IMAGE_USE}
ASSIMP_USE=${ASSIMP_USE}
SPDLOG_USE=${SPDLOG_USE}
IMGUI_USE=${IMGUI_USE}
)

# include path
target_include_directories(${PROJECT_NAME} PUBLIC ./include)
# include, link for dependencies
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${DEP_LIBS}
    "-framework CoreVideo"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework Carbon"
    "-framework QuartzCore"
)

file(COPY ${PROJECT_SOURCE_DIR}/src/shader DESTINATION ${PROJECT_BINARY_DIR}/src)

# dependency check
add_dependencies(${PROJECT_NAME} ${DEP_LIST})