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
#include "components/lab.hpp"

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

/**
 * @brief Función para iniciar sesión.
 * 
 * Esta función solicita al usuario que ingrese su ID de usuario y contraseña.
 * Luego, establece el ID de usuario y el estado de conexión en la estructura CurrentlyLoggedUser.
 * Si el ID de usuario y la contraseña corresponden a un superusuario, se establece el nivel de acceso del usuario en CurrentlyLoggedUser a verdadero.
 * De lo contrario, se establece a falso.
 */
void login() {
    int userID; ///< Variable para almacenar el ID de usuario ingresado.
    string pass; ///< Variable para almacenar la contraseña ingresada.
    int intentos=0;///< Variable para almacenar el número de intentos.
    cout << "Ingrese su userID de usuario: "; ///< Solicita al usuario que ingrese su ID de usuario.
    cin >> userID; ///< Almacena el ID de usuario ingresado en la variable userID.
    cin.ignore(); ///< Limpia la entrada de la pantalla.
    fflush(stdin); ///< Limpia la entrada de la pantalla.
    cout << "Ingrese su contraseña: "; ///< Solicita al usuario que ingrese su contraseña.
    solicitarContrasena(pass); ///< Almacena la contraseña ingresada en la variable pass.
    // cin.ignore(); ///< Limpia la entrada de la pantalla.
    // fflush(stdin); ///< Limpia la entrada de la pantalla.
    CurrentlyLoggedUser::s_userID(userID); ///< Establece el ID de usuario en la estructura CurrentlyLoggedUser.

    CurrentlyLoggedUser::s_logged(true); ///< Establece el estado de conexión en la estructura CurrentlyLoggedUser a verdadero.
    if (userID == SUPERUSER && pass == SUPERPASS) { ///< Comprueba si el ID de usuario y la contraseña corresponden a un superusuario.
        CurrentlyLoggedUser::s_userAccessLevel(true); ///< Si es un superusuario, establece el nivel de acceso en la estructura CurrentlyLoggedUser a verdadero.
    } else {
        CurrentlyLoggedUser::s_userAccessLevel(false); ///< Si no es un superusuario, establece el nivel de acceso en la estructura CurrentlyLoggedUser a falso.
    }
    cout<<userID<<endl;
    cout<<pass<<endl;
    cout<<"Probando"<<endl;
    getline(cin, pass, '\n');


    return; ///< Termina la función.
}

void solicitarContrasena(string &password) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);

    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    
    getline(cin, password, '\n');

    SetConsoleMode(hStdin, mode);

    return;
}