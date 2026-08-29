cmake_minimum_required(VERSION 4.3)
project(Recherche_de_nombre_premiers)

set(CMAKE_CXX_STANDARD 23)

add_executable(Recherche_de_nombre_premiers main.cpp
        Nombre.cpp
        Nombre.h
        ChercheurPremiers.cpp
        ChercheurPremiers.h
        Chronometre.cpp
        Chronometre.h
        CalculateurPremiers.cpp
        CalculateurPremiers.h)
