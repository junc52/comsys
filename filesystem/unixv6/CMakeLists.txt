cmake_minimum_required(VERSION 3.10)
project(diskimageaccess C)

# Enable all common warnings
set(CMAKE_C_FLAGS "${CMKAE_C_FLAGS} -g -Wall -W -Wcast-qual -Wwrite-strings -Wextra -Wno-unused -fstack-protector -std=gnu99")

# Find OpenSSL (required by chksumfile.c) External library
find_package(OpenSSL REQUIRED)

#Library source files
set(LIB_SRC
    diskimg.c
    inode.c
    unixfilesystem.c
    directory.c 
    pathname.c  
    chksumfile.c
    file.c )

add_library(v6fslib STATIC ${LIB_SRC})

# Main Program
add_executable(diskimageaccess diskimageaccess.c)

# Link with the library and OpenSSL
target_link_libraries(diskimageaccess v6fslib OpenSSL::SSL OpenSSL::Crypto)
