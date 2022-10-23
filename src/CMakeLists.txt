# CMakeList.txt : CMake project for AudioProcessor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("effects")
include_directories("effects")

add_subdirectory("console")
include_directories("console")

# Add source to this project's executable.
add_executable (AudioProcessor "main.cpp" "effects/Echo.cpp" "effects/Amplify.cpp" "console/ConsoleParser.cpp" "console/ConsoleProcessor.cpp" "effects/Delay.h" "effects/Delay.cpp")

# Audio processing library


# Link argument parcing library
target_include_directories("AudioProcessor" PUBLIC cxxopts)
target_link_libraries("AudioProcessor" PUBLIC cxxopts)
