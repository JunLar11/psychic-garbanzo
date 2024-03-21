//Código para el manejo de los materiales que pueden ser prestados
#include "headers/materials.hpp"

#include"headers/helpers.hpp"

void addMaterial(){
    Materials user,existantUser;
    string result,email;
    fflush(stdin);
    cin.clear();
    cin.ignore();
    
    string entrada;
    char correcto='s';
    do{
        system("cls");
        cout<<"Registro de materiales"<<endl;
        cout<<"\tIngrese el nombre del material: ";
        getline(cin,entrada,'\n');
        user.setNombre(entrada);
        cout<<"\tIngrese el codigo del material: ";
        getline(cin,entrada,'\n');
        user.setId(entrada);
        cout<<"\tIngrese la descripcion del material: ";
        getline(cin,entrada,'\n');
        user.setDescripcion(entrada);
        cout<<"\tIngrese la cantidad del material: ";
        getline(cin,entrada,'\n');
        user.setCantidad(entrada);
        user.setCanidadPrestada("0");

        entrada=user.getId();
        findMaterialInDb(result, entrada);
        existantUser.fromString(result);
        if(existantUser.getId()==user.getId()){
            cout<<"El material ya existe"<<endl;
            existantUser.show();
            cout<<endl;
            system("pause");
            return;
        }

        cout<<endl<<"\tDATOS REGISTRADOS:"<<endl;
        user.show();
        cout<<"\t¿Es correcto? (s/n): ";
        cin>>correcto;
        cin.clear();
        cin.ignore();
        fflush(stdin);
        if(correcto!='s' && correcto!= 'S'){
            return;
        }
    }while(correcto!='s' && correcto!= 'S');
    ofstream archivo;
    archivo.open(MATERIALS_TABLE_NAME, ios::app);
    archivo<<user.toString();
    archivo.close();
}

bool findMaterialInDb(string &registro, string &expediente){
    ifstream file(MATERIALS_TABLE_NAME, ios::in);
    string line;
    Materials user;
    while (getline(file, line,'\n')) {
        //mas estricta la busqueda
        user.fromString(line);
        if(user.getId()==expediente){
            registro=line;
            return true;
        }
    }
    return false;
}

void updateMaterial(){
    Materials user,newUser,existantUser;
    string result;
    string expediente="";
    string existente="";
    string expediente2="";
    fflush(stdin);
    cin.clear();
    cin.ignore();
    cout<<"Modificación de Materiales"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el codigo del material: ";
    cin>>expediente;
    findMaterialInDb(result, expediente);
    newUser.fromString(result);
    if(newUser.getId()==expediente){
        do{
            newUser.show();
            result=newUser.toString();
            user.fromString(result);
            cin.clear();
            cin.ignore();
            fflush(stdin);
            cout<<"\t¿Desea modificar el nombre? (s/n): ";
            cin>>correcto;
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);  
                cout<<"\tIngrese el nuevo nombre del material: ";
                getline(cin,entrada,'\n');
                user.setNombre(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar la descripcion? (s/n): ";
            cin>>correcto;
            
            
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese la nueva descripcion del material: ";

                getline(cin,entrada,'\n');
                user.setDescripcion(entrada);
            }
            cin.clear();
            fflush(stdin);
            cout<<"\t¿Desea modificar la cantidad? (s/n): ";
            cin>>correcto;
            if(correcto =='s' || correcto == 'S'){
                cin.clear();
                cin.ignore();
                fflush(stdin);
                cout<<"\tIngrese la nueva cantidad del material: ";
                getline(cin,entrada,'\n');
                user.setCantidad(entrada);
            }
            
            expediente2=user.getId();
            findMaterialInDb(existente, expediente2);
            existantUser.fromString(existente);
            if(existantUser.getId()!=user.getId()&&existantUser.getNombre()==user.getNombre()&&existantUser.getDescripcion()==user.getDescripcion()&&existantUser.getCantidad()==user.getCantidad()){
                cout<<"El código ya existe"<<endl;
                existantUser.show();
                cout<<endl;
                system("pause");
                break;
            }
            if(existantUser.getId()==user.getId()&&existantUser.getNombre()==user.getNombre()&&existantUser.getDescripcion()==user.getDescripcion()&&existantUser.getCantidad()==user.getCantidad()){
                cout<<"El material ya existe:"<<endl<<endl;
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
                updateLine(MATERIALS_TABLE_NAME, result, expediente);
                system("pause");
            }
            


            
        }while(correcto!='s' && correcto!= 'S');
    }else{
        cout<<"El material no existe"<<endl;
        system("pause");
        cout<<"¿Desea registrar un nuevo material? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            addMaterial();

        }
    }
    return;
}
void deleteMaterial(){
    Materials user;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();

    cin.ignore();
    cout<<"Eliminación de materiales"<<endl;
    string entrada;
    char correcto='s';
    cout<<"\tIngrese el codigo del material: ";
    cin>>expediente;
    findMaterialInDb(result, expediente);
    user.fromString(result);
    if(user.getId()==expediente){
        user.show();
        cout<<"\t¿Desea eliminar el material? (s/n): ";
        cin>>correcto;
        if(correcto =='s' || correcto == 'S'){
            deleteFromFile(MATERIALS_TABLE_NAME, result);
            cout<<"Material eliminado"<<endl;
            system("pause");
        }
    }else{
        cout<<"El material no existe"<<endl;
        system("pause");
        
    }
}

void getAllMaterials(){
    vector<string> users;
    Materials user;
    cout<<"Mostrando todos los materiales registrados"<<endl;
    getAllFromFile(MATERIALS_TABLE_NAME, users);
    for(int i=0; i<users.size(); i++){
        cout<<"------------Material "<<i+1<<"------------"<<endl;
        user.fromString(users[i]);
        user.show();
    }
    system("pause");
}
void getAMaterial(){
    Materials user;
    string result;
    string expediente="";
    fflush(stdin);
    cin.clear();
    cout<<"Busqueda de un material"<<endl;
    cout<<"Ingrese el código del material: ";
    cin>>expediente;
    findMaterialInDb(result, expediente);
    if(result.empty()){
        cout<<"El material no existe"<<endl;
        system("pause");
        return;
    }
    user.fromString(result);
    user.show();
    system("pause");
}