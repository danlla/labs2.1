﻿# CMakeList.txt: проект CMake для labs2.1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("labs2.1")

# Добавьте источник в исполняемый файл этого проекта.

add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
