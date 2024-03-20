


#get all files in directory

set(
    DYN_ARRAY_TEST_EXEC
    dyn_array_init_test
    dyn_array_get_field_test
    dyn_array_set_field_test
    dyn_array_resize_test
    dyn_array_push_test
    dyn_array_pop_test
    dyn_array_insert_at_test
    dyn_array_pop_at_test
)


set(
    DYN_ARRAY_TEST_SRCS
    dyn_array_init_test.c
    dyn_array_get_field_test.c
    dyn_array_set_field_test.c
    dyn_array_resize_test.c
    dyn_array_push_test.c
    dyn_array_pop_test.c
    dyn_array_insert_at_test.c
    dyn_array_pop_at_test.c
)

set(I 0)
set(INDEX 0)

set(EXEC)
set(SRC)



list(LENGTH DYN_ARRAY_TEST_EXEC I)


while(INDEX LESS I)

    list(GET DYN_ARRAY_TEST_EXEC ${INDEX} EXEC)
    list(GET DYN_ARRAY_TEST_SRCS ${INDEX} SRC)

    add_executable(${EXEC} ${SRC})


    add_test(
        NAME ${EXEC}
        COMMAND $<TARGET_FILE:${EXEC}>
    )


    target_link_libraries(${EXEC} PUBLIC asta)

    MATH(EXPR INDEX ${INDEX}+1)
endwhile()



