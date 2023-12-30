cmake_minimum_required(VERSION 3.5)

project(projet_fin_de_module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(projet_fin_de_module main.cpp
    cdate.h cdate.cpp)

include(GNUInstallDirs)
install(TARGETS projet_fin_de_module
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
