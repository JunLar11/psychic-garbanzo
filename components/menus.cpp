//Código de los distintos menus usados a lo largo del programa
#include "headers/menus.hpp"
#include "headers/sessions.hpp"
bool mainMenu(vector<MemPrestamos> &prestamos){
    //vector<User> users;
    //users.reserve(10);
    
    

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
            //cout<<"\t5. Reportes"<<endl;
        }
        cout<<"\t'S'.Salir"<<endl;
        //cout<<"\t'C'.Cerrar sesión"<<endl;
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
                salir = userMenu();
                break;
            case '2':
                salir = prestamosMenu(prestamos);
                break;
            case '3':
                salir = materialsMenu();
                break;
            case '4':
                salir = laboratoristasMenu();
                break;
            case '5':
                break;
            case 'C':
            case 'c':
                CurrentlyLoggedUser::logout();
                return true;
            case 'S':
            case 's':
                CurrentlyLoggedUser::logout();
                return false;
            default:
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                fflush(stdin);
                
                
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

bool userMenu(){
    
    char opcion='r';
    string expediente="";
    do{
        
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
        cout<<"\t5. Buscar usuario"<<endl;
        cout<<"\t'R'. Regresar al menú principal"<<endl;
        cout<<"\t'S'. Salir del programa"<<endl;
        cout<<"\tIngrese una opción: ";

        cin>>opcion;
        fflush(stdin);
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\tADMINISTRACION DE USUARIOS"<<endl;
        
        switch(opcion){
            case '1':
                
                addUser();
                
                break;
            case '2':
                updateUser();
                
                
                break;
            case '3'://Eliminar usuario
                deleteUser();
                break;
            case '4':
                getAllUsers();
                break;
            case '5':
                getAUser();
                break;
            case 'R':
            case 'r':
                return false;
            case 'S':
            case 's':
                return true;
            default:
                fflush(stdin);
                cin.clear();
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                Sleep(2000);
                break;
        }
    }while(opcion!='r'||opcion!='R'||opcion!='s'||opcion!='S');
    return true;
}
bool materialsMenu(){
    
    char opcion='r';
    string expediente="";
    do{
        
        fflush(stdin);
        cin.clear();
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\t\tMENU MATERIALES"<<endl;
        cout<<"\tElige una de las siguientes opciones:"<<endl;
        cout<<"\t1. Agregar material"<<endl;
        cout<<"\t2. Modificar material"<<endl;
        cout<<"\t3. Eliminar material"<<endl;
        cout<<"\t4. Consultar materiales"<<endl;
        cout<<"\t5. Buscar material"<<endl;
        cout<<"\t'R'. Regresar al menú principal"<<endl;
        cout<<"\t'S'. Salir del programa"<<endl;
        cout<<"\tIngrese una opción: ";

        cin>>opcion;
        fflush(stdin);
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\tADMINISTRACION DE MATERIALES"<<endl;
        
        switch(opcion){
            case '1':
                
                addMaterial();
                
                break;
            case '2':
                updateMaterial();
                
                
                break;
            case '3'://Eliminar usuario
                deleteMaterial();
                break;
            case '4':
                getAllMaterials();
                break;
            case '5':
                getAMaterial();
                break;
            case 'R':
            case 'r':
                return false;
            case 'S':
            case 's':
                return true;
            default:
                fflush(stdin);
                
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                Sleep(2000);
                break;
        }
    }while(opcion!='r'||opcion!='R'||opcion!='s'||opcion!='S');
    return true;
}

bool laboratoristasMenu(){
    
    char opcion='r';
    string expediente="";
    do{
        
        fflush(stdin);
        cin.clear();
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\t\tMENU LABORATORISTAS"<<endl;
        cout<<"\tElige una de las siguientes opciones:"<<endl;
        cout<<"\t1. Agregar laboratoristas"<<endl;
        cout<<"\t2. Modificar laboratoristas"<<endl;
        cout<<"\t3. Eliminar laboratoristas"<<endl;
        cout<<"\t4. Consultar laboratoristass"<<endl;
        cout<<"\t5. Buscar laboratoristas"<<endl;
        cout<<"\t'R'. Regresar al menú principal"<<endl;
        cout<<"\t'S'. Salir del programa"<<endl;
        cout<<"\tIngrese una opción: ";
        
        cin>>opcion;
        fflush(stdin);
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\tADMINISTRACION DE LABORATORISTAS"<<endl;
        
        switch(opcion){
            case '1':
                
                addLab();
                
                break;
            case '2':
                updateLab();
                
                
                break; 
            case '3'://Eliminar usuario
                deleteLab();
                break;
            case '4':
                getAllLabs();
                break;
            case '5':
                getALab();
                break;
            case 'R':
            case 'r':
                return false;
            case 'S':
            case 's':
                return true;
            default:
                fflush(stdin);
                
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                Sleep(2000);
                break;
        }
    }while(opcion!='r'||opcion!='R'||opcion!='s'||opcion!='S');
    return true;
}
bool prestamosMenu(vector<MemPrestamos> &prestamos){
    
    char opcion='r';
    string expediente="";
    do{
        
        fflush(stdin);
        cin.clear();
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\t\tMENU PRESTAMOS"<<endl;
        cout<<"\tElige una de las siguientes opciones:"<<endl;
        cout<<"\t1. Realizar prestamo"<<endl;
        //cout<<"\t2. Modificar prestamo"<<endl;
        cout<<"\t2. Consultar devoluciones pendientes"<<endl;
        cout<<"\t3. Realizar devolucion"<<endl;
        cout<<"\t'R'. Regresar al menú principal"<<endl;
        cout<<"\t'S'. Salir del programa"<<endl;
        cout<<"\tIngrese una opción: ";
        
        cin>>opcion;
        fflush(stdin);
        system("cls");
        cout<<"\t\t\t\tSistema de Administración del Laboratorio"<<endl;
        cout<<"\tADMINISTRACION DE LABORATORISTAS"<<endl;
        
        switch(opcion){
            case '1':
                
                prestar(prestamos);
                
                break;
            case '2':
                consultarPrestamosPendientes(prestamos);
                
                
                break; 
            case '3'://Eliminar usuario
                devolver(prestamos);
                break;
                
            case 'R':
            case 'r':
                return false;
            case 'S':
            case 's':
                return true;
            default:
                fflush(stdin);
                
                cout<<endl<<"\tIngrese una opción válida"<<endl;
                Sleep(2000);
                break;
        }
    }while(opcion!='r'||opcion!='R'||opcion!='s'||opcion!='S');
    return true;
}