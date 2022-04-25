cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(CGDraw)

set(CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} CGDraw.cpp Model.cpp World.cpp Models.cpp Group.cpp Camera.cpp Lights.cpp Groups.cpp Transform.cpp)

# link cartesian
add_subdirectory(cartesian)

# vcpkg install [freeglut, glew, tinyxml2]

#add OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#add tinyxml
find_package(tinyxml2 REQUIRED)

# add glut
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

#add Glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})


target_include_directories(CGDraw PUBLIC cartesian)

target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLUT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC GLUT::GLUT)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PUBLIC tinyxml2::tinyxml2)
target_link_libraries(${PROJECT_NAME} PUBLIC cartesian)

if(WIN32)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
else (WIN32)
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
endif(WIN32)

# GENERATOR EXECUTABLE
add_executable(generator generator/shapes.h generator/shapes.cpp generator/writer.h generator/writer.cpp)
target_link_libraries(generator tinyxml2::tinyxml2)
target_link_libraries(generator cartesian)
target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(generator GLUT::GLUT)
#target_link_libraries(generator m)
#target_include_directories(generator PUBLIC cartesian)
