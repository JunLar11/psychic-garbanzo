//Este archivo contiene las cabeceras de las funciones que se van a utilizar para los menús de la aplicación.
#pragma once 
#include "prjheaders.hpp"

#include "lab.hpp"
#include "materials.hpp"
#include "borrow.hpp"
#include "user.hpp"



bool mainMenu(vector<MemPrestamos> &prestamos);
bool userMenu();

bool laboratoristasMenu();

bool materialsMenu();

bool prestamosMenu(vector<MemPrestamos> &prestamos);