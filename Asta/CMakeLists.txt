
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(ASTA_SOURCES 
    src/Asta/Engine/Engine.c
    src/Asta/Platform/Platform.c
    src/Asta/Renderer/Renderer.c
    
    src/Asta/Util/Logger/Logger.c
    src/Asta/Util/Memory/Memory.c

    src/Asta/Containers/dyn_array.c
)


#Third party dependencies


#GLFW
add_subdirectory(libs/glfw)
find_package(glfw)


#Cunit

set(LIBRARY_NAME asta)

#OPENGL

find_package(OPENGL REQUIRED)


# GLAD

add_subdirectory(libs/glad)

set(EXTERNAL_LIBS
  glfw
  glad
)

add_compile_definitions(ADEBUG)



add_library(${LIBRARY_NAME} SHARED ${ASTA_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

if(DARWIN)
    add_compile_definitions(ASTA_PLATFORM_MACOS=1)
endif()

target_link_libraries(${LIBRARY_NAME} ${EXTERNAL_LIBS} OpenGL::GL)

