# CMake configuration for the example
cmake_minimum_required(VERSION 3.5)

# Define the executable
add_executable(${PROJECT_NAME}_example main.cpp)

# Link the library
target_link_libraries(${PROJECT_NAME}_example PRIVATE ${PROJECT_NAME})
