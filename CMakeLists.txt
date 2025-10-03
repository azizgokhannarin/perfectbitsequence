cmake_minimum_required(VERSION 3.5)

project(FuseByte LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
    fusebyte.cpp
    main.cpp
)

set(HEADERS
    fusebyte.h
)

add_executable(FuseByte ${SOURCES} ${HEADERS})

install(TARGETS FuseByte
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
