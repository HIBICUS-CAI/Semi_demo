cmake_minimum_required(VERSION 3.15)
project(Semi_demo)

set(CMAKE_CXX_STANDARD 14)

#添加头文件
set(SDL2_H /usr/local/include/SDL2)
set(GLEW_H /usr/local/include/GL)
set(GLM_H /usr/local/include/glm)
include_directories(${SDL2_H} ${GLEW_H} ${GLM_H})

#添加目标链接
set(SDL2_LINK /usr/local/lib/libSDL2.dylib)
set(GLEW_LINK /usr/local/lib/libGLEW.dylib)
link_libraries(${SDL2_LINK} ${GLEW_LINK} ${SOIL_LINK})

aux_source_directory(src/. DIRS_SRCS)

add_executable(Semi_demo ${DIRS_SRCS})


#if判断是否为Mac系统，如果是就执行在GOS项目中加入OpenGL的动态库文件，此处是因为GLEW需要OpenGL
if (APPLE)
    target_link_libraries(Semi_demo "-framework OpenGL")
endif()