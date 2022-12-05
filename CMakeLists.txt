cmake_minimum_required(VERSION 3.23)
project(Final_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Final_Project
        Die.c
        Die.h
        main.c
        Mugwump.h
        Warrior.h
        Warrior.c
        Mugwump.c)
