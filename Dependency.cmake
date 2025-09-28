include(FetchContent)

set(DEP_INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)
set(CMAKE_INSTALL_PREFIX ${DEP_INSTALL_DIR})

# spdlog
FetchContent_Declare(dep_spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG "v1.x"
    GIT_SHALLOW 1
)
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog::spdlog)
set(SPDLOG_INSTALL ON CACHE BOOL "") # 이거 안해주면 build에 install이 안생김

# glfw
FetchContent_Declare(dep_glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG "3.3.2"
    GIT_SHALLOW 1
)

set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_INSTALL ON CACHE BOOL "") # 이거 안해주면 build에 install이 안생김
# FetchContent에 선언된 모든 항목을 프로젝트에 포함시킵니다.
FetchContent_MakeAvailable(${DEP_LIST})
