cmake_minimum_required(VERSION 3.10)
project(ProjetLivraison)

set(CMAKE_CXX_STANDARD 23)

add_executable(interfaceConsole
    interfaceConsole.cpp
    Agence.cpp
    Avion.cpp
    Camion.cpp
    Client_agence.cpp
    Destinataire.cpp
    Drone.cpp
    Personne.cpp
    Velo.cpp
    colis.cpp
)

