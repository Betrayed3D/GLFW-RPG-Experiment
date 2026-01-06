cmake_minimum_required(VERSION 3.10.0)
project(RPGExperiment VERSION 0.1.0)

include_directories("C:\\Users\\Marcus\\Documents\\Linking\\Includes\\GLAD" "C:\\Users\\Marcus\\Documents\\Linking\\Includes\\GLFW")
link_directories("C:\\Users\\Marcus\\Documents\\Linking\\Libraries\\glfw")

add_executable(RPGExperiment src/main.cpp C:\\Users\\Marcus\\Documents\\Linking\\Includes\\glad\\glad.c)

target_link_libraries(RPGExperiment PUBLIC "C:\\Users\\Marcus\\Documents\\Linking\\Libraries\\glfw\\glfw3.lib")