cmake_minimum_required(VERSION 3.12)

project( OPENCV_SERIAL_DESERIAL )

find_package(Protobuf REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS image.proto)

find_package( OpenCV REQUIRED )
find_package(eCAL REQUIRED)

add_executable( Serialization serialization.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries( Serialization eCAL::core ${OpenCV_LIBS} ${Protobuf_LIBRARIES} )

add_executable( Deserialization deserialization.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries( Deserialization eCAL::core ${OpenCV_LIBS} ${Protobuf_LIBRARIES} )
