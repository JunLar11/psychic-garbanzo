#pragma once
#include "sessions.hpp"
string CurrentlyLoggedUser::userID=""; ///< El ID del usuario actualmente conectado.
bool CurrentlyLoggedUser::userAccessLevel=false; ///< El nivel de acceso del usuario actualmente conectado. Verdadero para acceso de alto nivel, falso para acceso de bajo nivel.
bool CurrentlyLoggedUser::logged=false; ///< El estado de conexión del usuario. Verdadero si el usuario está conectado, falso de lo contrario.
string CurrentlyLoggedUser::name=""; ///< El nombre del usuario actualmente conectado.

