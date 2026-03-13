cmake_minimum_required(VERSION 3.16)
project(BattleshipGame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(include)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BattleshipGame
    main.cpp
    src/MyWidget.cpp
    src/Field.cpp
    src/Ship.cpp
    src/GameWindow.cpp
    src/PlacementShipsBot.cpp
    src/Battlefield.cpp
    src/BattlefieldUIX.cpp
    src/ShooterBot.cpp
    src/ShipItem.cpp
)

target_link_libraries(BattleshipGame
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(RunTests 
    tests/FieldTest.cpp
    tests/ShipTest.cpp
    src/Ship.cpp
    src/Field.cpp
)

target_link_libraries(RunTests
    GTest::gtest_main
    GTest::gmock
)

enable_testing()
add_test(NAME AllTests COMMAND RunTests)