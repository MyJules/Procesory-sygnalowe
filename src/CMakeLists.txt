# CMakeList.txt : CMake project for AudioProcessor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory("effects")
include_directories("effects")

# Add source to this project's executable.
add_executable (AudioProcessor "main.cpp")

# Echo
target_link_libraries("AudioProcessor" PUBLIC effectsLib)

# Link argument parcing library
target_include_directories("AudioProcessor" PUBLIC cxxopts)
target_link_libraries("AudioProcessor" PUBLIC cxxopts)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AudioProcessor PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
