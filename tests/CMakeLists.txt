

#Test executable

add_executable(ctest test.c)

add_test(
    NAME ctest
    COMMAND $<TARGET_FILE:ctest>
)
