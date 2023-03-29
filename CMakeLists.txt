cmake_minimum_required(VERSION 3.21)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 14)

# Setup the locations that the GLEW libraries can be found on disk
set(GLEW_INCLUDE_DIR C:/libs/GLEW/include/GL) # set(VAR_NAME path)
set(GLEW_LIB_DIR C:/libs/GLEW/lib/Release/x64) # set(VAR_NAME path)

# Setup the locations that GLFW libraries can be found
set(GLFW_INCLUDE_DIR C:/libs/GLFW/include/GLFW) # set(VAR_NAME path)
set(GLFW_LIB_DIR C:/libs/GLFW/lib-mingw-w64) # set(VAR_NAME path)

# Setup the locations that GLFW libraries can be found
set(GLM_INCLUDE_DIR C:/libs/GLM) # set(VAR_NAME path)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${GLEW_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*
include_directories(${GLFW_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*
include_directories(${GLM_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*

link_directories(${GLEW_LIB_DIR}) # link_directories(${VAR_NAME}) *used for dll/binary/lib files*
link_directories(${GLFW_LIB_DIR}) # link_directories(${VAR_NAME}) *used for dll/binary/lib files*

add_executable(VoxelEngine main.cpp Colour.h Colour.cpp ColourRandomizer.h ColourRandomizer.cpp DeltaTime.h DeltaTime.cpp Enumerators.h Enumerators.cpp Random.h Random.cpp OpenGLApp.cpp OpenGLApp.h Scene.cpp Scene.h Camera.cpp Camera.h Object.cpp Object.h Triangle.cpp Triangle.h RenderObject.cpp RenderObject.h SceneManager.cpp SceneManager.h TestingScene.cpp TestingScene.h Cube.cpp Cube.h Chunk.cpp Chunk.h VoxelWorld.cpp VoxelWorld.h Voxel.cpp Voxel.h Structures.cpp Structures.h)

target_link_libraries(${PROJECT_NAME} glfw3 glew32 opengl32 -static-libgcc -static-libstdc++) # Link the libraries to the project
