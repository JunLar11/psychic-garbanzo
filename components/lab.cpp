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

    fflush(stdin);
    cin.clear();
    //Disable cin.ignore()
    //cout << "\tIngrese su contraseña: ";
    getline(cin, password, '\n');

    SetConsoleMode(hStdin, mode);

    return;
}

string passWordCipher(string &passWord){
    string passWordCipher = "";
    for (int i = 0; i < passWord.length(); i++) {
        passWordCipher += passWord[i] + 3;
        //Aplicar AND con respecto al caracter original
        if(passWord[i] % 2 == 0){
            passWordCipher[i] += passWordCipher[i] - 1;
        }
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
    Laboratorista lab;
    ifstream file(LAB_TABLE_NAME, ios::in);
    string line;
    while (getline(file, line,'\n')) {
        lab.getFromString(line);
        if (lab.getId() == labID) {
            result = lab.toString();
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
            registro = lab.getPassword();
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


void addLab(){
    Laboratorista user,existantUser;
    string result,email;
    fflush(stdin);
    cin.clear();
    cin.ignore();
    
    string entrada;
    char correcto='s';
    do{
        system("cls");
        cout<<"Registro de laboratoristas"<<endl;
        cout<<"Ingrese su nombre: ";
        cin>>entrada;
        cin.ignore();
        user.setNombre(entrada);
        //cin.ignore();
        cin.clear();
        fflush(stdin);
        
        cout<<"Ingrese su contraseña: ";
        solicitarContrasena(entrada);

        user.setPassword(passWordCipher(entrada));
        cout<<"Ingrese su telefono: ";
        cin>>entrada;
        user.setTelefono(entrada);
        cout<<"Ingrese su turno: ";
        cin>>entrada;
        user.setTurno(entrada);
        cout<<"Ingrese su ID: ";
        cin>>entrada;
        user.setId(entrada);

        entrada=user.getId();
        findLabInDb(result, entrada);
        existantUser.getFromString(result);
        if(existantUser.getId()== entrada){
            cout<<"El ID ingresado ya existe"<<endl;
            existantUser.show();
            cout<<endl;
            system("pause");
            return;
        }
        entrada=user.getTelefono();
        findLabInDb(result, entrada);
        existantUser.getFromString(result);
        if(existantUser.getTelefono()==user.getTelefono()){
            cout<<"El telefono ya existe"<<endl;
            existantUser.show();
            cout<<endl;
            system("pause");
            return;
        }

        cout<<endl<<"\tDATOS REGISTRADOS:"<<endl;
        user.show();
        cout<<"\t¿Es correcto? (s/n): ";
        cin>>correcto;
        if(correcto!='s' && correcto!= 'S'){
            return;
        }

    }while(correcto!='s' && correcto!= 'S');
    ofstream archivo;
    archivo.open(LAB_TABLE_NAME, ios::app);
    archivo<<user.toString();
    archivo.close();
}

bool findLabInDb(string &registro, string &expediente){
    ifstream file(LAB_TABLE_NAME, ios::in);
    string line;
    Laboratorista user;
    while (getline(file, line,'\n')) {
        //mas estricta la busqueda
        user.getFromString(line);
        if(user.getId()==expediente||user.getTelefono()==expediente){
            registro=line;
            return true;

        }
    }
    return false;
}

void updateLab(){
    Laboratorista user,newUser,existantUser;
    string result;
    string expediente="";
    string existente="";
    string expediente2="";
    fflush(stdin);
    cin.clear();
    cin.ignore();
    cout<<"Modificación de laboratoristas"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el expediente o telefono del laboratorista: ";
    cin>>expediente;
    findLabInDb(result, expediente);
    newUser.getFromString(result);
    if(newUser.getId()==expediente || newUser.getTelefono()==expediente){
        do{
            newUser.show();
            result=newUser.toString();
            user.getFromString(result);
            cin.clear();
            cin.ignore();
            fflush(stdin);
            cout<<"\t¿Desea modificar el nombre? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);  
                cout<<"\tIngrese el nuevo nombre del laboratorista: ";
                getline(cin, entrada, '\n');
                user.setNombre(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar el numero de telefono? (s/n): ";
            cin>>correcto;
            
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese el nuevo telefono del laboratorista: ";
                getline(cin, entrada, '\n');
                user.setTelefono(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar la contraseña? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese la nueva contraseña del laboratorista: ";
                solicitarContrasena(entrada);
                user.setPassword(passWordCipher(entrada));
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar el turno? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese el nuevo turno del laboratorista: ";
                getline(cin, entrada, '\n');
                user.setTurno(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar el ID? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese el nuevo ID del laboratorista: ";
                getline(cin, entrada, '\n');
                user.setId(entrada);
            }
            expediente2=user.getId();
            findLabInDb(existente, expediente2);
            existantUser.getFromString(existente);

            if(existantUser.getId()==user.getId()&&existantUser.getTelefono()!=user.getTelefono()&&existantUser.getNombre()!=user.getNombre()){
                cout<<"El ID ya existe:"<<endl<<endl;
                existantUser.show();
                cout<<endl;
                system("pause");
                break;
            }
            expediente2=user.getTelefono();
            findLabInDb(existente, expediente2);
            existantUser.getFromString(existente);
            if(existantUser.getId()!=user.getId()&&existantUser.getTelefono()==user.getTelefono()&&existantUser.getNombre()!=user.getNombre()){
                cout<<"El telefono ya existe:"<<endl<<endl;
                existantUser.show();
                cout<<endl;
                system("pause");
                break;
            }
            if(existantUser.getId()==user.getId()&&existantUser.getTelefono()==user.getTelefono()&&existantUser.getNombre()==user.getNombre()&&existantUser.getPassword()==user.getPassword()){
                cout<<"El laboratorista ya existe:"<<endl<<endl;
                existantUser.show();
                cout<<endl;
                system("pause");
                break;
            }
            
            
            user.show();
            fflush(stdin);
            cin.clear();
            cout<<"\t¿Es correcto? (s/n): ";
            cin>>correcto;
            if(correcto =='s' || correcto == 'S'){
                result=user.toString();
                expediente=newUser.toString();
                updateLine(LAB_TABLE_NAME, expediente, result);
                system("pause");
            }
            


            
        }while(correcto!='s' && correcto!= 'S');
    }else{
        cout<<"El laboratorista no existe"<<endl;
        system("pause");
        cout<<"¿Desea registrar un nuevo laboratorista? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            addLab();

        }
    }
    return;
}
void deleteLab(){
    Laboratorista user;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();

    cin.ignore();
    cout<<"Eliminación de laboratoristas"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el expediente o correo electronico del laboratorista: ";
    cin>>expediente;
    findLabInDb(result, expediente);
    user.getFromString(result);
    if(user.getId()==expediente || user.getTelefono()==expediente){
        user.show();
        cout<<"\t¿Desea eliminar el laboratorista? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            deleteFromFile(LAB_TABLE_NAME, result);
            cout<<"Laboratorista eliminado"<<endl;
            system("pause");
        }
    }else{
        cout<<"El laboratorista no existe"<<endl;
        system("pause");
        
    }
}

void getAllLabs(){
    vector<string> users;
    Laboratorista user;
    cout<<"Mostrando todos los laboratoristas registrados"<<endl;
    getAllFromFile(LAB_TABLE_NAME, users);
    for(int i=0; i<users.size(); i++){
        cout<<"------------Laboratorista "<<i+1<<"------------"<<endl;
        user.getFromString(users[i]);
        user.show();
    }
    system("pause");
}
void getALab(){
    Laboratorista user;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();
    cout<<"Busqueda de un laboratorista"<<endl;
    cout<<"Ingrese el expediente o telefono del laboratorista: ";
    cin>>expediente;
    findLabInDb(result, expediente);
    if(result.empty()){
        cout<<"El laboratorista no existe"<<endl;
        system("pause");
        return;
    }
    user.getFromString(result);
    user.show();
    system("pause");
}