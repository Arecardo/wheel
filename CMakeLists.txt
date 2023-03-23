cmake_minimum_required(VERSION 2.8)

project(log_test)

############################################################
# Create a library
############################################################

# Generate the static library from the library sources
add_library(Logger STATIC 
    src/log/Logger.cpp
)

target_include_directories(Logger 
    PUBLIC
        src/log
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(test_log 
    test/log/main.cpp
)

# link the new Logger target with the test_log target
target_link_libraries(test_log
    PRIVATE
        Logger
)