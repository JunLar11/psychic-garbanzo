//Código para el manejo de los laboratoristas

//#include "headers/sessions.hpp"
#include "headers/lab.hpp"
#include "headers/sessioninit.hpp"

//Métodos de la estructura Laboratorista
Laboratorista::Laboratorista(string id, string nombre, string password, string telefono, string turn) {
    this->id = id;
    this->nombre = nombre;
    this->password = password;
    this->telefono = telefono;
    this->turno = turn;
}

Laboratorista::Laboratorista(string &registro){
    //Formato de un registro: id,nombre,password,telefono,turno;
    //Sacar los datos por medio de string
    getFromString(registro);
}

Laboratorista::Laboratorista() {
    this->id = "";
    this->nombre = "";
    this->password = "";
    this->telefono = "";
    this->turno = "";
}

string Laboratorista::getId() {
    return this->id;
}

string Laboratorista::getNombre() {
    return this->nombre;
}

string Laboratorista::getPassword() {
    return this->password;
}

string Laboratorista::getTelefono() {
    return this->telefono;
}

string Laboratorista::getTurno() {
    return this->turno;
}

void Laboratorista::setId(string id) {
    this->id = id;
}

void Laboratorista::setNombre(string nombre) {
    this->nombre = nombre;
}

void Laboratorista::setPassword(string password) {
    this->password = password;
}

void Laboratorista::setTelefono(string telefono) {
    this->telefono = telefono;
}

void Laboratorista::setTurno(string turno) {
    this->turno = turno;
}

void Laboratorista::getFromString(string &registro) {
    stringstream ss(registro);
    string nombre, password, telefono,_id,turno;
    getline(ss, _id, ',');
    getline(ss, nombre, ',');
    getline(ss, password, ',');
    getline(ss, telefono, ',');
    getline(ss, turno, ';');

    this->id = _id;
    this->nombre = nombre;
    this->password = password;
    this->telefono = telefono;
    this->turno = turno;
}


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
    ifstream file(LAB_TABLE_NAME, ios::in);
    string line;
    while (getline(file, line,'\n')) {
        if (line.find(labID) != string::npos) {
            result = line;
            return true;
        }
    }
    return false;
}

void parseLaboratorista(string &line, Laboratorista &lab) {

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
    string userID; ///< Variable para almacenar el ID de usuario ingresado.
    string pass; ///< Variable para almacenar la contraseña ingresada.
    string registro; ///< Variable para almacenar el registro de usuario ingresado.
    int intentos=0;///< Variable para almacenar el número de intentos.
    Laboratorista lab; ///< Variable para almacenar el registro de usuario ingresado.
    do{
        cout << " _     _______  _______  _     __    __" << endl;
        cout << "| |   | _____ || ______|| |   |  \\ |  |" << endl;
        cout << "| |   | |   | || |      | |   |   \\|  |" << endl;
        cout << "| |   | |   | || |  ___ | |   |  |\\   | " << endl;
        cout << "| |___| |___| || |_|_  || |   |  | \\  |" << endl;
        cout<<  "|_____|_______||_______||_|   |__|  \\_|" << endl;
        cout <<endl<< "\tIngrese su userID de usuario: "; ///< Solicita al usuario que ingrese su ID de usuario.
        cin >> userID; ///< Almacena el ID de usuario ingresado en la variable userID.
        cin.ignore(); ///< Limpia la entrada de la pantalla.
        fflush(stdin); ///< Limpia la entrada de la pantalla.
        cout << "\tIngrese su contraseña: "; ///< Solicita al usuario que ingrese su contraseña.
        solicitarContrasena(pass); ///< Almacena la contraseña ingresada en la variable pass.
        // cin.ignore(); ///< Limpia la entrada de la pantalla.
        // fflush(stdin); ///< Limpia la entrada de la pantalla.
        if (userID == SUPERUSER && pass == SUPERPASS) { ///< Comprueba si el ID de usuario y la contraseña corresponden a un superusuario.
            CurrentlyLoggedUser::login("Administrador", true, SUPERUSER,true); ///< Establece el ID de usuario y el estado de conexión en la estructura CurrentlyLoggedUser.
            return; ///< Termina la función.
        }else if(searchLaboratorista(userID, registro)){
            lab.getFromString(registro);
            if(verifyPassword(pass, registro)){
                CurrentlyLoggedUser::login(lab.getNombre(), true, lab.getId());
                return; 
            }else{
                cout << "Contraseña incorrecta" << endl;
                
            }
        }else{
            cout << "Usuario no encontrado" << endl;
            
        }
        intentos++;
        Sleep(2000);
        system("cls");
        cout<<"Intentos restantes: " << 5-intentos << endl;
    }while(intentos < 5);
    
    cout << "Demasiados intentos fallidos, intente más tarde" << endl;
    Sleep(2000);
    exit(1);

    return; ///< Termina la función.
}
