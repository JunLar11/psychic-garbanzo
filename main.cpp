//Programa para la administración de el laboratorio de automatización
/*
El programa debe de estar hecho con estructuras y vectores.
Se van a crear cuatro estructuras:
-Laboratorista
   >Nombre
   >userID
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

/**
 * @struct CurrentlyLoggedUser
 * @brief Una estructura para representar al usuario actualmente conectado.
 * 
 * Esta estructura contiene miembros estáticos para mantener el ID del usuario, el nivel de acceso y el estado de conexión.
 * Proporciona métodos getter y setter estáticos para estos miembros.
 */
struct CurrentlyLoggedUser {
private:
    static int userID; ///< El ID del usuario actualmente conectado.
    static bool userAccessLevel; ///< El nivel de acceso del usuario actualmente conectado. Verdadero para acceso de alto nivel, falso para acceso de bajo nivel.
    static bool logged; ///< El estado de conexión del usuario. Verdadero si el usuario está conectado, falso de lo contrario.

public:
    /**
     * @brief Obtener el ID del usuario
     * 
     * @return int El ID del usuario actualmente conectado.
     */
    static int g_userID() {
        return CurrentlyLoggedUser::userID;
    }

    /**
     * @brief Establecer el ID del usuario
     * 
     * @param _userID El nuevo ID de usuario a establecer.
     */
    static void s_userID(int _userID) {
        CurrentlyLoggedUser::userID = _userID;
    }

    /**
     * @brief Obtener el nivel de acceso del usuario
     * 
     * @return bool El nivel de acceso del usuario actualmente conectado.
     */
    static bool g_userAccessLevel() {
        return CurrentlyLoggedUser::userAccessLevel;
    }

    /**
     * @brief Establecer el nivel de acceso del usuario
     * 
     * @param _userAccessLevel El nuevo nivel de acceso a establecer. Verdadero para acceso de alto nivel, falso para acceso de bajo nivel.
     */
    static void s_userAccessLevel(bool _userAccessLevel) {
        CurrentlyLoggedUser::userAccessLevel = _userAccessLevel;
    }

    /**
     * @brief Obtener el estado de conexión
     * 
     * @return bool El estado de conexión del usuario.
     */
    static bool g_logged() {
        return CurrentlyLoggedUser::logged;
    }

    /**
     * @brief Establecer el estado de conexión
     * 
     * @param _logged El nuevo estado de conexión a establecer. Verdadero si el usuario está conectado, falso de lo contrario.
     */
    static void s_logged(bool _logged) {
        CurrentlyLoggedUser::logged = _logged;
    }
};

int CurrentlyLoggedUser::userID = 0;
bool CurrentlyLoggedUser::userAccessLevel = false;
bool CurrentlyLoggedUser::logged = false;

void login();

void solicitarContrasena(string &password);

int main() {
    //Creando los archivos de texto necesarios
    creadorArchivos(LAB_TABLE_NAME);
    creadorArchivos(MATERIALS_TABLE_NAME);
    creadorArchivos(BORROW_TABLE_NAME);
    creadorArchivos(USERS_TABLE_NAME);

    // Obtener el manejador de la ventana de consola
    HWND hwnd = GetConsoleWindow();

    // Establecer el ícono de la ventana de consola
    // HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    // SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    // SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    SetConsoleTitleA("Lab. Admin");

    // Mostrar la ventana de consola en la barra de tareas
    ShowWindow(hwnd, SW_SHOW);
    login();
    mainMenu();
    system("pause");
    exit(0);
    return 0;
}

