cmake_minimum_required(VERSION 3.10)
project(Worksheet5)

# Library
add_library(maths adder.cpp)

# Executable
add_executable(calc calc.cpp)
target_link_libraries(calc maths)

# Install rules for CPack
if(WIN32)
    set(CPACK_GENERATOR "NSIS")
else()
    set(CPACK_GENERATOR "ZIP")
endif()

install(TARGETS calc maths
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

include(CPack)
