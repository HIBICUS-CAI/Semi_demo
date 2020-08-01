cmake_minimum_required(VERSION 3.15)
project(Semi_demo)

set(CMAKE_CXX_STANDARD 14)

message("Project's pwd is : ${CMAKE_CURRENT_SOURCE_DIR}")

#添加头文件
set(SDL2_H ${CMAKE_CURRENT_SOURCE_DIR}/lib/head/SDL2)
set(GLEW_H ${CMAKE_CURRENT_SOURCE_DIR}/lib/head/GL)
set(GLM_H ${CMAKE_CURRENT_SOURCE_DIR}/lib/head/glm)
set(JSON_H ${CMAKE_CURRENT_SOURCE_DIR}/lib/head/json)
include_directories(${SDL2_H} ${GLEW_H} ${GLM_H} ${JSON_H})

#添加目标链接
set(SDL2_LINK ${CMAKE_CURRENT_SOURCE_DIR}/lib/dylib/libSDL2.dylib)
set(GLEW_LINK ${CMAKE_CURRENT_SOURCE_DIR}/lib/dylib/libGLEW.dylib)
set(JSON_LINK ${CMAKE_CURRENT_SOURCE_DIR}/lib/dylib/libjsoncpp.dylib)
set(SDL2TTF_LINK ${CMAKE_CURRENT_SOURCE_DIR}/lib/dylib/libSDL2_ttf.dylib)
link_libraries(${SDL2_LINK} ${GLEW_LINK} ${JSON_LINK} ${SDL2TTF_LINK})

aux_source_directory(src/. DIRS_SRCS)

add_executable(Semi_demo ${DIRS_SRCS})


#if判断是否为Mac系统，如果是就执行在GOS项目中加入OpenGL的动态库文件，此处是因为GLEW需要OpenGL
if (APPLE)
    target_link_libraries(Semi_demo "-framework OpenGL")
endif()