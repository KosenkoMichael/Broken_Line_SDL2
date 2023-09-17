cmake_minimum_required(VERSION 3.11)

project(makemake)

set(CMAKE_CXX_STANDARD 23)

# Специфичные настройки для компилятора Visual Studio
if(MSVC)
    # Генерируем статическую заглушку для динамических библиотек
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2 PATHS "SDL2/cmake")
include_directories("SDL2/include")

# Библиотека
add_library(functions SHARED "functions/include/broken_line.h" "functions/broken_line.cc")

# exe-шник
add_executable(console WIN32 "console/main.cc")
target_link_libraries(console   PUBLIC functions
                                PRIVATE SDL2::SDL2)

add_custom_command(TARGET console POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:console> $<TARGET_FILE_DIR:console>
    COMMAND_EXPAND_LISTS
)

# Подключаем googletest
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# exe с тестами
add_executable(tests "tests/tests.cc")
target_link_libraries(tests functions GTest::gtest_main)