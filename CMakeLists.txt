cmake_minimum_required(VERSION 4.0)
project(BattleshipGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BattleshipGame main.cpp)
target_link_libraries(BattleshipGame
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
