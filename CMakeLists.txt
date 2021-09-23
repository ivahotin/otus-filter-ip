cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ipfilter VERSION ${PROJECT_VESRION})

# Add directory with gtest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

configure_file(version.h.in version.h)

add_executable(ipfilter_cli main.cpp)
add_library(ipfilter_lib lib.cpp)
add_executable(unit_tests test_version.cpp)

set_target_properties(ipfilter_cli ipfilter_lib unit_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ipfilter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ipfilter_cli PRIVATE
    ipfilter_lib
)
target_link_libraries(unit_tests
    gtest
    gtest_main
    ipfilter_lib
)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(ipfilter_cli PRIVATE
        /W4
    )
    target_compile_options(ipfilter_lib PRIVATE
        /W4
    )
    target_compile_options(unit_tests PRIVATE
        /W4
    )
else ()
    target_compile_options(ipfilter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ipfilter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(unit_tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ipfilter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(unit_tests unit_tests)