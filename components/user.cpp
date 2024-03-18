//Código para el manejo de usuarios como lo serían alumnos y maestros que deseen material prestado
#include"headers/user.hpp"
#include"headers/helpers.hpp"

User addUser(){
    User user;
    string result;
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
        if(findUserInDb(result, entrada)){
            cout<<"El usuario ya existe:"<<endl<<endl;
            user.setFromString(result);
            user.show();
            system("pause");
            return user;
        }
        cout<<endl<<"\tDATOS REGISTRADOS:"<<endl;
        user.show();
        cout<<"\t¿Es correcto? (s/n): ";
        cin>>correcto;

    }while(correcto!='s' && correcto!= 'S');
    ofstream archivo;
    archivo.open(USERS_TABLE_NAME, ios::app);
    archivo<<user.toString();
    archivo.close();
    return user;
}

bool findUserInDb(string &registro, string &expediente){
    ifstream file(USERS_TABLE_NAME, ios::in);
    string line;
    while (getline(file, line,'\n')) {
        if (line.find(expediente) != string::npos) {
            registro = line; 
            return true;
        }
    }
    return false;
}

User updateUser(){
    User user,newUser;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();
    cin.ignore();
    cout<<"Modificación de usuarios"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el expediente o correo electronico del usuario: ";
    cin>>expediente;
    if(findUserInDb(result, expediente)){
        do{
            newUser.setFromString(result);
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
            cin.ignore();
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
            cin.ignore();
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
            cin.ignore();
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
            cin.ignore();
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

            user.show();
            fflush(stdin);
            cin.clear();
            cout<<"\t¿Es correcto? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                result=newUser.getExpediente();
                expediente=user.toString();
                updateLine(USERS_TABLE_NAME, result, expediente);
                system("pause");
                return user;
            }
        }while(correcto!='s' && correcto!= 'S');
    }else{
        cout<<"El usuario no existe"<<endl;
        system("pause");
        cout<<"¿Desea registrar un nuevo usuario? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            return addUser();

        }
    }
    return user;
}