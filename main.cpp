//Programa para la administración de el laboratorio de automatización
/*
El programa debe de estar hecho con estructuras y vectores.
Se van a crear cuatro estructuras:
-Laboratorista
   >Nombre
   >Clave
   >Correo
   >Telefono
   >Turno
-Material
   >ID
   >Nombre
   >Cantidad
   >Ubicación
   >Descripción
-Préstamo
   >ID
   >Materiales
   >Materia
   >Fecha préstamos
   >Fecha de devolución
   >Observaciones
   >Laboratorista
-Usuario
   >Expediente
   >Nombre
   >Correo
   >Telefono
   >Carrera
*/

#include "components/menus.hpp"

#define SUPERUSER 13032024
#define SUPERPASS "SPadBal2024"

using namespace std;

struct currentlLogged {
private:
    static int clave;
    static bool accessLevel;

public:
    static int g_clave() {
        return currentlLogged::clave;
    }

    static void s_clave(int _clave) {
        currentlLogged::clave = _clave;
    }

    static bool g_accessLevel() {
        return currentlLogged::accessLevel;
    }

    static void s_accessLevel(bool _accessLevel) {
        currentlLogged::accessLevel = _accessLevel;
    }
};

int currentlLogged::clave = 0;
bool currentlLogged::accessLevel = false;

void login();

int main() {
    login();
    mainMenu();
    system("pause");
    
    return 0;
}

void login() {
    int clave;
    string pass;

    cout << "Ingrese su clave de usuario: ";
    cin >> clave;

    cout << "Ingrese su contraseña: ";
    cin >> pass;

    currentlLogged::s_clave(clave);

    if (clave == SUPERUSER && pass == SUPERPASS) {
        currentlLogged::s_accessLevel(true);
        cout << "Eres SUPER!";
    } else {
        currentlLogged::s_accessLevel(false);
        cout << "Eres normal!";
    }

    return;
}