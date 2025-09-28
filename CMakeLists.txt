cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

set(PROJECT_NAME opengl)
set(CMAKE_CXX_STANDARD 20)

set(WINDOW_NAME "OpenGL")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
project(${PROJECT_NAME})

include(Dependency.cmake)

add_executable (${PROJECT_NAME} 
"src/main.cpp"
"src/common.cpp"  "src/common.h"
"src/shader.cpp"  "src/shader.h" 
)

# Configure project include and library options
# 타겟을 링킹할 때 필요한 헤더 지정
# src도 포함해야한다!
target_include_directories(${PROJECT_NAME} PRIVATE
    ${DEP_INCLUDE_DIR}
    src
)
# 타겟을 링킹할 때 필요한 라이브러리 지정
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})


target_compile_definitions(${PROJECT_NAME} PUBLIC
	WINDOW_NAME="${WINDOW_NAME}"
	WINDOW_WIDTH=${WINDOW_WIDTH}
	WINDOW_HEIGHT=${WINDOW_HEIGHT}
	)



FetchContent_Declare(dep_glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        glad2
    GIT_PROGRESS   TRUE
    SOURCE_SUBDIR  cmake
)
FetchContent_MakeAvailable(dep_glad)
glad_add_library(glad_gl_core_43 STATIC REPRODUCIBLE LOADER API gl:core=4.3)
target_link_libraries(${PROJECT_NAME} PRIVATE glad_gl_core_43)
