if (WIN32)
    # Patch CMake's 'add_test' to extend the DLL search path on Windows. Use the
    # target name associated with the test, if it is also a CMake target.

    macro(add_test)
        _add_test(${ARGV})

        cmake_parse_arguments("" "" "NAME" "" ${ARGV})
        string(REGEX MATCH "^[^_]+" _DLL_TARGET "${_NAME}")
        set(DLL_DIRS $<TARGET_RUNTIME_DLL_DIRS:${_DLL_TARGET}>)
        set_tests_properties(${_NAME}
            PROPERTIES ENVIRONMENT
            "PATH=$<JOIN:$<SHELL_PATH:${DLL_DIRS}>,\\;>")
    endmacro()
endif()

set(testWrapper "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/testWrapper.py" --verbose)

add_executable(testJsIO testJsIO.cpp)
target_link_libraries(testJsIO PUBLIC js)

add_test(NAME testJsIO_PlugInfo
    COMMAND ${testWrapper} "$<TARGET_FILE:testJsIO> plugInfo.json.in plugInfo.json"
    "--testenv-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO"
    "--baseline-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO/baseline"
    --diff-compare=plugInfo.json)

add_test(NAME testJsIO_Values
    COMMAND ${testWrapper} "$<TARGET_FILE:testJsIO> values.json.in values.json"
    "--testenv-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO"
    "--baseline-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO/baseline"
    --diff-compare=values.json)

add_test(NAME testJsIO_Errors_BadCommaPlacement
    COMMAND ${testWrapper} "$<TARGET_FILE:testJsIO> bad-commaPlacement.json -"
    "--testenv-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO_Errors"
    "--baseline-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO_Errors/baseline"
    --stderr-redirect=testJsIO_Errors-Run1-stderr.txt
    --diff-compare=testJsIO_Errors-Run1-stderr.txt
    --expected-return-code=2)

add_test(NAME testJsIO_Errors_MismatchedBraces
    COMMAND ${testWrapper} "$<TARGET_FILE:testJsIO> bad-mismatchedBraces.json -"
    "--testenv-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO_Errors"
    "--baseline-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsIO_Errors/baseline"
    --stderr-redirect=testJsIO_Errors-Run2-stderr.txt
    --diff-compare=testJsIO_Errors-Run2-stderr.txt
    --expected-return-code=2)

add_executable(testJsConverter testJsConverter.cpp)
target_link_libraries(testJsConverter PUBLIC js)
add_test(NAME testJsConverter COMMAND testJsConverter)

add_executable(testJsUtils testJsUtils.cpp)
target_link_libraries(testJsUtils PUBLIC js)
add_test(NAME testJsUtils COMMAND testJsUtils)

add_executable(testJsWriter testJsWriter.cpp)
target_link_libraries(testJsWriter PUBLIC js)

add_test(NAME testJsWriter
    COMMAND ${testWrapper} "$<TARGET_FILE:testJsWriter> test.json compact"
    "--testenv-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsWriter"
    "--baseline-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsWriter/baseline"
    --diff-compare=test.json)

add_test(NAME testJsWriter_Pretty
    COMMAND ${testWrapper} "$<TARGET_FILE:testJsWriter> test-pretty.json pretty"
    "--testenv-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsWriter"
    "--baseline-dir=${CMAKE_CURRENT_SOURCE_DIR}/testJsWriter/baseline"
    --diff-compare=test-pretty.json)

add_executable(testJsDouble testJsDouble.cpp)
target_link_libraries(testJsDouble PUBLIC js pxr::tf pxr::arch)
add_test(NAME testJsDouble COMMAND testJsDouble)
