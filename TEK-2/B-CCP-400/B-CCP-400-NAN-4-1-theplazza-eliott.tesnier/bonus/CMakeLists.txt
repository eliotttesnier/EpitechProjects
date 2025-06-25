cmake_minimum_required(VERSION 3.16)
project(plazza LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 QUIET COMPONENTS Core Widgets)

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "src/*.hpp"
)

# Exclude GUI sources if Qt is not found
if(NOT Qt6_FOUND)
    list(FILTER SOURCES EXCLUDE REGEX ".*/GUI/.*")
    list(FILTER HEADERS EXCLUDE REGEX ".*/GUI/.*")
    message(STATUS "Qt6 not found - building without GUI support")
    add_compile_definitions(NO_GUI)
else()
    message(STATUS "Qt6 found - building with GUI support")
    add_compile_definitions(GUI_ENABLED)

    # Enable Qt MOC
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

# Create executable
add_executable(plazza ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(plazza PRIVATE pthread)

if(Qt6_FOUND)
    target_link_libraries(plazza PRIVATE Qt6::Core Qt6::Widgets)
endif()

# Include directories
target_include_directories(plazza PRIVATE src)
target_include_directories(plazza PRIVATE lib)

# Compiler flags
target_compile_options(plazza PRIVATE -Wall -Wextra -g)

set_target_properties(plazza PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
