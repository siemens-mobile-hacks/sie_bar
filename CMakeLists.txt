cmake_minimum_required(VERSION 3.31)

include(../sdk/config.cmake)
project(sieelf_sie_bar C)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable(SieBar_ELKA ${SOURCES})

target_sdk_setup(SieBar_ELKA ELKA)
target_link_libraries(SieBar_ELKA PRIVATE crt crt_helper c gcc)
target_compile_definitions(SieBar_ELKA PRIVATE SWILIB_MODERN)
target_compile_options(SieBar_ELKA PRIVATE -Wall -Werror)
set_target_properties(SieBar_ELKA PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
        OUTPUT_NAME "SieBar"
)
