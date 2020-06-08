cmake_minimum_required(VERSION 3.10)

project(Assignment)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)
include_directories(src)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS tree.proto)

add_executable(main
    src/main.cpp
    include/tree_serializer.h
    include/tree.h
    src/tree_serializer.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS})
target_link_libraries(main ${Protobuf_LIBRARIES})
