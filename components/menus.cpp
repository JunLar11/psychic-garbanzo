//Código de los distintos menus usados a lo largo del programa
#include "headers/menus.hpp"
#include "headers/sessions.hpp"
bool mainMenu(){
    vector<User> users;
    users.reserve(10);

    

    system("cls");
    cout<<"\t\t\t\tSistema de Administración del Laboratorio\n\t\t\tde Automatización de la Ingeniería en Automatización de la UAQ"<<endl;
    cout<<"\tBienvenido de vuelta: "<<CurrentlyLoggedUser::g_name()<<endl;  
    char opcion='s';
    bool salir=false;
    do{
        system("cls");
        cin.clear();
        fflush(stdin);
        cout<<"Ingrese una de las siguientes opciones:"<<endl;
        cout<<"\t1. Usuarios"<<endl;
        cout<<"\t2. Préstamos"<<endl;
        cout<<"\t3. Materiales"<<endl;
        if(CurrentlyLoggedUser::g_userAccessLevel()){
            cout<<"\t4. Laboratoristas"<<endl;
            cout<<"\t5. Reportes"<<endl;
        }
        cout<<"\t'S'.Salir"<<endl;
        cout<<"\t'C'.Cerrar sesión"<<endl;
        cout<<"\tIngrese una opción: ";
        cin>>opcion;
        fflush(stdin);
        if((opcion=='5'||opcion=='4')&&!CurrentlyLoggedUser::g_userAccessLevel()){
            cout<<endl<<"\tNo tiene permisos para acceder a esta opción"<<endl;
            Sleep(2000);
            continue;
        }
        switch(opcion){
            case '1':
                salir = userMenu(users);
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case 'C':
            case 'c':
                CurrentlyLoggedUser::logout();
                return true;
            case 'S':
            case 's':
                return false;
            default:
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                Sleep(2000);
                break;
        }
        if(salir==true){
            return !salir;
        }
        system("cls");
        cout<<"Desea salir? (S/N): ";
        cin>>opcion;
        fflush(stdin);
        if(opcion=='s'||opcion=='S'){
            return false;
        }

    }while(opcion!='s'||opcion!='S'||salir);
    return false;
}

bool userMenu(vector<User> &users){
    
    char opcion='r';
    bool inMemory=false;
    do{
        User user;
        fflush(stdin);
        cin.clear();
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\t\tMENU USUARIOS"<<endl;
        cout<<"\tElige una de las siguientes opciones:"<<endl;
        cout<<"\t1. Agregar usuario"<<endl;
        cout<<"\t2. Modificar usuario"<<endl;
        cout<<"\t3. Eliminar usuario"<<endl;
        cout<<"\t4. Consultar usuarios"<<endl;
        cout<<"\t5. Reporte usuarios"<<endl;
        cout<<"\t'R'. Regresar al menú principal"<<endl;
        cout<<"\t'S'. Salir del programa"<<endl;
        cout<<"\tIngrese una opción: ";
        cin>>opcion;
        fflush(stdin);
        switch(opcion){
            case '1':
                
                user=addUser();
                for(int i=0;i<users.size();i++){
                    if(users[i].getExpediente()==user.getExpediente()){
                        inMemory=true;
                    }
                }
                if(!inMemory){
                    users.push_back(user);
                }
                break;
            case '2':
                user=updateUser();
                
                if(user.getExpediente()==""){
                    break;
                }
                for(int i=0;i<users.size();i++){
                    if(users[i].getExpediente()==user.getExpediente()){
                        inMemory=true;
                    }
                }
                if(!inMemory){
                    users.push_back(user);
                }
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case 'R':
            case 'r':
                return false;
            case 'S':
            case 's':
                return true;
            default:
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                Sleep(2000);
                break;
        }

        inMemory=false;
    }while(opcion!='r'||opcion!='R'||opcion!='s'||opcion!='S');
    return true;
}

