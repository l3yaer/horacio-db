cmake_minimum_required(VERSION 3.13)
project(horacioDB C)

set(CMAKE_C_STANDARD 99)

add_executable(horacioDB main.c statement.c input.c metaCommand.c table.c pager.c cursor.c)