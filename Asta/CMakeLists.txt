
#GLFW
add_subdirectory(libs/glfw)
find_package(glfw)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(ASTA_SOURCES 
    src/Asta/Core/Engine/Engine.c
    src/Asta/Core/Window/Window.c
    src/Asta/Core/Events/Event.c
    src/Asta/Util/Logger/Logger.c
    src/Asta/Util/Memory/Memory.c
    src/Asta/Containers/Vector/Vector.c
)

#Third party dependencies
set(EXTERNAL_LIBS
  glfw
)

#OPENGL

find_package(OPENGL REQUIRED)





add_library(AstaEngine SHARED ${ASTA_SOURCES})

target_include_directories(AstaEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)






if(DARWIN)
    add_compile_definitions(ASTA_PLATFORM_MACOS=1)
endif()



target_link_libraries(AstaEngine ${EXTERNAL_LIBS} OpenGL::GL)
