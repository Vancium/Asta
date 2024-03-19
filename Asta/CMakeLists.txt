
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(ASTA_SOURCES 
    src/Asta/Core/Engine/Engine.c
    src/Asta/Core/Platform/Platform.c
    src/Asta/Util/Logger/Logger.c
    src/Asta/Util/Memory/Memory.c
)

#Third party dependencies


#GLFW
add_subdirectory(libs/glfw)
find_package(glfw)

#Cunit

set(LIBRARY_NAME asta)


set(EXTERNAL_LIBS
  glfw
)

#OPENGL

find_package(OPENGL REQUIRED)




add_compile_definitions(ADEBUG)



add_library(${LIBRARY_NAME} SHARED ${ASTA_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

if(DARWIN)
    add_compile_definitions(ASTA_PLATFORM_MACOS=1)
endif()

target_link_libraries(${LIBRARY_NAME} ${EXTERNAL_LIBS} OpenGL::GL)

