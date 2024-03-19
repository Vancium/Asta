

#get all files in directory

set(
    MEMORY_TEST_EXEC
    memory_init_test
    memory_allocate_test
    memory_free_test
    memory_zero_test
    memory_set_test
    memory_copy_test
)

set(
    MEMORY_TEST_SRCS
    memory_init_test.c
    memory_allocate_test.c
    memory_free_test.c
    memory_zero_test.c
    memory_set_test.c
    memory_copy_test.c
)

set(I 0)
set(INDEX 0)

set(EXEC)
set(SRC)



list(LENGTH MEMORY_TEST_EXEC I)


while(INDEX LESS I)

    list(GET MEMORY_TEST_EXEC ${INDEX} EXEC)
    list(GET MEMORY_TEST_SRCS ${INDEX} SRC)

    add_executable(${EXEC} ${SRC})


    add_test(
        NAME ${EXEC}
        COMMAND $<TARGET_FILE:${EXEC}>
    )


    target_link_libraries(${EXEC} PUBLIC asta)

    MATH(EXPR INDEX ${INDEX}+1)
endwhile()



