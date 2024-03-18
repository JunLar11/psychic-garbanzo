//Código para el manejo de los laboratoristas

#include "headers/sessions.hpp"
#include "headers/lab.hpp"


//CurrentlyLoggedUser currentSession; ///< Estructura para almacenar el estado de conexión y el nivel de acceso del usuario actual.

void solicitarContrasena(string &password) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);

    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    
    getline(cin, password, '\n');

    SetConsoleMode(hStdin, mode);

    return;
}

string passWordCipher(string &passWord){
    string passWordCipher = "";
    for(int i = 0; i < passWord.length(); i++){
        passWordCipher += passWord[i];
        passWordCipher[i]=passWordCipher[i] + 3;
        //Aplicar operacion NOT
        passWordCipher[i] = ~passWordCipher[i];
        //Aplicar la operacion OR respecto al caracter original
        passWordCipher[i] = passWordCipher[i] | passWord[i];
        passWordCipher[i] = passWordCipher[i] ^ passWord[i];
        passWordCipher[i] = passWordCipher[i] & passWord[i];
    }
    return passWordCipher;
}

bool verifyPassword(string &passWord, string &passWordCiphered){
    if(passWordCiphered == passWordCipher(passWord)){
        return true;
    }
    return false;
}

bool searchLaboratorista(string &labID, string &result) {
    ifstream file("laboratorios.txt");
    string line;
    while (getline(file, line)) {
        if (line.find(labID) != string::npos) {
            result = line;
            return true;
        }
    }
    return false;
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
    CurrentlyLoggedUser::s_userAccessLevel(false);
    CurrentlyLoggedUser::s_userID(userID); ///< Establece el ID de usuario en la estructura CurrentlyLoggedUser.

    CurrentlyLoggedUser::s_logged(true); ///< Establece el estado de conexión en la estructura CurrentlyLoggedUser a verdadero.
    if (userID == SUPERUSER && pass == SUPERPASS) { ///< Comprueba si el ID de usuario y la contraseña corresponden a un superusuario.
        CurrentlyLoggedUser::s_userAccessLevel(true); ///< Si es un superusuario, establece el nivel de acceso en la estructura CurrentlyLoggedUser a verdadero.
    } else {
        //if()
        CurrentlyLoggedUser::s_userAccessLevel(false); ///< Si no es un superusuario, establece el nivel de acceso en la estructura CurrentlyLoggedUser a falso.
    }
    



    return; ///< Termina la función.
}

