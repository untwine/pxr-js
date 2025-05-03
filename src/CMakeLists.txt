configure_file(
    pxr/js/pxr.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/pxr/js/pxr.h
    @ONLY
)

add_library(js
    pxr/js/json.cpp
    pxr/js/utils.cpp
    pxr/js/value.cpp
)

target_include_directories(js
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Compile features can only raise the effective standard, so this can't be
# undercut by a toolchain file that pre-sets CMAKE_CXX_STANDARD lower.
target_compile_features(js PUBLIC cxx_std_17)

target_link_libraries(js
    PUBLIC
        pxr::arch
        pxr::tf
)

if(NOT WIN32 AND NOT SKBUILD)
    set_target_properties(js PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

if (ENABLE_PRECOMPILED_HEADERS)
    target_precompile_headers(js
        PRIVATE
            pxr/js/pch.h
    )
endif()

set_target_properties(js
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        OUTPUT_NAME "PxrJs"
)

target_compile_definitions(js
    PRIVATE
        JS_EXPORTS=1
        MFB_PACKAGE_MODULE=Js
        MFB_PACKAGE_NAME=js
        MFB_ALT_PACKAGE_NAME=js
)

target_sources(js
    PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/pxr/js/pxr.h
            pxr/js/api.h
            pxr/js/converter.h
            pxr/js/json.h
            pxr/js/types.h
            pxr/js/utils.h
            pxr/js/value.h
)

install(
    TARGETS js EXPORT ${PROJECT_NAME}
    FILE_SET public_headers
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT ${PROJECT_NAME}
    FILE pxr-js-targets.cmake
    NAMESPACE pxr::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/pxr-js
)