# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("AudioProcessor")

# Argument parcing library 
add_subdirectory("extern/cxxopts")

# Audio processing library
add_subdirectory("extern/kfr")

# Logging library
add_subdirectory("extern/spdlog")
include_directories("extern/spdlog/include")

# Include sub-projects.
add_subdirectory ("src")
