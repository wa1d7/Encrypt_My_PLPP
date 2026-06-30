cmake_minimum_required(VERSION 4.2)
project(Encrypt)

set(CMAKE_CXX_STANDARD 20)

add_library(cipher SHARED cipher.cpp)

set_target_properties(cipher PROPERTIES PREFIX "")

add_executable(Encrypt main.cpp
        include/cipher_api.h
        line.cpp
        line.h
        text.cpp
        text.h
        cipher_loader.cpp
        cipher_loader.h
        text_editor.cpp
        text_editor.h
)
add_custom_command(TARGET Encrypt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:cipher>
        $<TARGET_FILE_DIR:Encrypt>
)