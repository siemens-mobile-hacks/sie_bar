cmake_minimum_required(VERSION 3.28.2)

include(../sdk/config.cmake)
project(sieelf_sie_bar C)

include_directories("../libsie/src/include")
link_libraries(crt crt_helper c gcc m z png ft sie)
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(SieBar_ELKA ${SOURCES})
target_sdk_setup(SieBar_ELKA ELKA)
target_link_directories(SieBar_ELKA PUBLIC "../libsie/build/lib/ELKA")
target_compile_options(SieBar_ELKA BEFORE PUBLIC -std=gnu99 -Wall -Werror)
