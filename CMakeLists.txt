cmake_minimum_required(VERSION 4.2)
project(Encrypt)

set(CMAKE_CXX_STANDARD 20)

add_executable(Encrypt main.cpp
        cipher.cpp
        cipher.h
)
