cmake_minimum_required(VERSION 3.16)
project(BattleshipGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BattleshipGame main.cpp)

target_include_directories(BattleshipGame PRIVATE
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Gui_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
)

target_link_libraries(BattleshipGame
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
