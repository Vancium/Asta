
set (GAME_SRC src/Entry.c src/Game.c)
add_executable(game ${GAME_SRC})

target_link_libraries(game asta)
