# requires minimum cmake version
cmake_minimum_required(VERSION 2.8.9)

# produce the cmake var PROJECT_NAME
project(consumer)

# mandatory use of these packages
find_package(YARP REQUIRED)

include_directories(${YARP_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/consumer.cpp)
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES})

