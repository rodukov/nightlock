cmake_minimum_required(VERSION 3.14)
project(Nightlock LANGUAGES CXX)

# -- select C++20 standart --
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# -- .h/.hpp files --
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include    # собственные .h
    ${CMAKE_CURRENT_SOURCE_DIR}/requirements  # json.hpp
)

# --- OpenSSL ---
find_package(OpenSSL REQUIRED)
include_directories("C:/Program Files/OpenSSL-Win64/include")
link_directories("C:/Program Files/OpenSSL-Win64/lib")

add_executable(Nightlock
    src/kernel.cpp
    src/Database.cpp
    src/formatkit.cpp
    src/livecmd.cpp
    src/Manager.cpp
    src/split.cpp
   "src/Crypt.cpp" "include/Crypt.h" "include/readsecret.h" "src/readsecret.cpp")

target_link_libraries(Nightlock PRIVATE OpenSSL::SSL OpenSSL::Crypto)