cmake_minimum_required(VERSION 3.14)
project(Nightlock LANGUAGES CXX)

# Используем C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Пути к заголовочным файлам
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include    # собственные .h
    ${CMAKE_CURRENT_SOURCE_DIR}/requirements  # json.hpp
)

# Механизм для скачивания сторонних библиотек
include(FetchContent)

# Подключаем FTXUI
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# Создаём исполняемый файл Nightlock с исходниками из src/
add_executable(Nightlock
    src/kernel.cpp
    src/Database.cpp
    src/formatkit.cpp
    src/livecmd.cpp
    src/Manager.cpp
    src/split.cpp
)

# Линкуем FTXUI
target_link_libraries(Nightlock PRIVATE ftxui::screen ftxui::dom ftxui::component)
