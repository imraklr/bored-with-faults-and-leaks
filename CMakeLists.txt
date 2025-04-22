cmake_minimum_required(VERSION 3.19...3.29)
project(
    "bored-with-faults-and-leaks"
    DESCRIPTION "Efforts to develop secure constructs within the constraints of C's current syntax."
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11) # Minimum supported C version
set(CMAKE_C_STANDARD_REQUIRED ON)

# add executable for testing out the code that I have been typing till now
add_executable(App
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ingredients/ingredients.c"
)