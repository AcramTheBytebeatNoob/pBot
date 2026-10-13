cmake_minimum_required(VERSION 3.13)

project(pBotStudio)

find_package(Geode REQUIRED)

add_geode_mod(
    pbot
    SOURCES
        src/main.cpp
        src/modmenu.cpp
)
