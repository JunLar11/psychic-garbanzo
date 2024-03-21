//Código para el manejo de usuarios como lo serían alumnos y maestros que deseen material prestado
#include"headers/user.hpp"
#include"headers/helpers.hpp"

void addUser(){
    User user,existantUser;
    string result,email;
    fflush(stdin);
    cin.clear();
    cin.ignore();
    
    string entrada;
    char correcto='s';
    do{
        system("cls");
        cout<<"Registro de usuarios"<<endl;
        cout<<"\tIngrese el nombre del usuario: ";
        getline(cin, entrada, '\n');
        user.setNombre(entrada);
        cout<<"\tIngrese el correo electronico del usuario: ";
        getline(cin, entrada, '\n');
        user.setCorreo(entrada);
        cout<<"\tIngrese el teléfono del usuario: ";
        getline(cin, entrada, '\n');
        user.setTelefono(entrada);
        cout<<"\tIngrese el expediente del usuario: ";
        getline(cin, entrada, '\n');
        user.setExpediente(entrada);
        cout<<"\tIngrese la carrera del usuario: ";
        getline(cin, entrada, '\n');
        user.setCarrera(entrada);
        entrada=user.getExpediente();
        findUserInDb(result, entrada);
        existantUser.setFromString(result);
        if(existantUser.getCorreo()==user.getCorreo()){
            cout<<"El correo ya existe"<<endl;
            existantUser.show();
            cout<<endl;
            system("pause");
            return;
        }
        entrada=user.getExpediente();
        findUserInDb(result, entrada);
        existantUser.setFromString(result);
        if(existantUser.getExpediente()==user.getExpediente()){
            cout<<"El expediente ya existe"<<endl;
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
    archivo.open(USERS_TABLE_NAME, ios::app);
    archivo<<user.toString();
    archivo.close();
}

bool findUserInDb(string &registro, string &expediente){
    ifstream file(USERS_TABLE_NAME, ios::in);
    string line;
    User user;
    while (getline(file, line,'\n')) {
        //mas estricta la busqueda
        user.setFromString(line);
        if(user.getExpediente()==expediente||user.getCorreo()==expediente){
            registro=line;
            return true;
        }
    }
    return false;
}

void updateUser(){
    User user,newUser,existantUser;
    string result;
    string expediente="";
    string existente="";
    string expediente2="";
    fflush(stdin);
    cin.clear();
    cin.ignore();
    cout<<"Modificación de usuarios"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el expediente o correo electronico del usuario: ";
    cin>>expediente;
    findUserInDb(result, expediente);
    newUser.setFromString(result);
    if(newUser.getExpediente()==expediente||newUser.getCorreo()==expediente){
        do{
            newUser.show();
            result=newUser.toString();
            user.setFromString(result);
            cin.clear();
            cin.ignore();
            fflush(stdin);
            cout<<"\t¿Desea modificar el nombre? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);  
                cout<<"\tIngrese el nuevo nombre del usuario: ";
                getline(cin, entrada, '\n');
                user.setNombre(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar el correo electronico? (s/n): ";
            cin>>correcto;
            
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese el nuevo correo electronico del usuario: ";
                getline(cin, entrada, '\n');
                user.setCorreo(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar el teléfono? (s/n): ";
            cin>>correcto;
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese el nuevo teléfono del usuario: ";
                getline(cin, entrada, '\n');
                user.setTelefono(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar la carrera? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese la nueva carrera del usuario: ";
                getline(cin, entrada, '\n');
                user.setCarrera(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar el expediente? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese el nuevo expediente del usuario: ";
                getline(cin, entrada, '\n');
                user.setExpediente(entrada);
            }
            expediente2=user.getExpediente();
            findUserInDb(existente, expediente2);
            existantUser.setFromString(existente);
            if(existantUser.getExpediente()==user.getExpediente()&&existantUser.getCorreo()!=user.getCorreo()&&existantUser.getNombre()!=user.getNombre()){
                cout<<"El expediente ya existe:"<<endl<<endl;
                existantUser.show();
                cout<<endl;
                system("pause");
                break;
            }
            expediente2=user.getCorreo();
            findUserInDb(existente, expediente2);
            existantUser.setFromString(existente);
            if(existantUser.getExpediente()!=user.getExpediente()&&existantUser.getCorreo()==user.getCorreo()&&existantUser.getNombre()!=user.getNombre()){
                cout<<"El correo ya existe:"<<endl<<endl;
                existantUser.show();
                cout<<endl;
                system("pause");
                break;
            }
            if(existantUser.getExpediente()==user.getExpediente()&&existantUser.getCorreo()==user.getCorreo()&&existantUser.getNombre()==user.getNombre()){
                cout<<"El usuario ya existe:"<<endl<<endl;
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
                result=newUser.toString();
                expediente=user.toString();
                updateLine(USERS_TABLE_NAME, result, expediente);
                system("pause");
            }
            


            
        }while(correcto!='s' && correcto!= 'S');
    }else{
        cout<<"El usuario no existe"<<endl;
        system("pause");
        cout<<"¿Desea registrar un nuevo usuario? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            addUser();

        }
    }
    return;
}
void deleteUser(){
    User user;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();

    cin.ignore();
    cout<<"Eliminación de usuarios"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el expediente o correo electronico del usuario: ";
    cin>>expediente;
    findUserInDb(result, expediente);
    user.setFromString(result);
    if(user.getExpediente()==expediente || user.getCorreo()==expediente){
        user.show();
        cout<<"\t¿Desea eliminar el usuario? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            deleteFromFile(USERS_TABLE_NAME, result);
            cout<<"Usuario eliminado"<<endl;
            system("pause");
        }
    }else{
        cout<<"El usuario no existe"<<endl;
        system("pause");
        
    }
}

void getAllUsers(){
    vector<string> users;
    User user;
    cout<<"Mostrando todos los usuarios registrados"<<endl;
    getAllFromFile(USERS_TABLE_NAME, users);
    for(int i=0; i<users.size(); i++){
        cout<<"------------Usuario "<<i+1<<"------------"<<endl;
        user.setFromString(users[i]);
        user.show();
    }
    system("pause");
}
void getAUser(){
    User user;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();
    cout<<"Busqueda de un usuario"<<endl;
    cout<<"Ingrese el expediente o correo electronico del usuario: ";
    cin>>expediente;
    findUserInDb(result, expediente);
    if(result.empty()){
        cout<<"El usuario no existe"<<endl;
        system("pause");
        return;
    }
    user.setFromString(result);
    user.show();
    system("pause");
}