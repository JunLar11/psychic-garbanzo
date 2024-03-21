//Código para el manejo de los prestamos a realizar
#include "headers/borrow.hpp"
#include"headers/helpers.hpp"
#include"headers/user.hpp"
#include"headers/materials.hpp"
#include "headers/sessions.hpp"

void prestar(vector<MemPrestamos> &prestamosInMemory){
    Prestamos prestamos;
    MemPrestamos MemPrestamos;
    vector<string> materiales;
    vector<string> newFileMaterials;
    Materials materials;
    string result;
    int cantidad=0;
    fflush(stdin);
    cin.clear();
    cin.ignore();
    string material;
    bool enough=true;
    string entrada,expediente,otra,otra2,otra3;
    char correcto='s';
    do{
        system("cls");
        cout<<"Registro de prestamo"<<endl;
        cout<<"\tIngrese el expediente del usuario: ";
        getline(cin, entrada, '\n');
        
        for(int i=0; i<prestamosInMemory.size(); i++){
            if(prestamosInMemory[i].getUsuario()==entrada){
                cout<<"El usuario tiene un prestamo pendiente"<<endl;
                cout<<"Desea continuar? (s/n): ";
                cin>>correcto;
                if(correcto=='s' || correcto == 'S'){
                    break;
                }else{
                    return;
                }
            }
        }

        prestamos.setUsuario(entrada);
        //ºcout<<"\tIngrese la fecha de prestamo: ";
        //getline(cin, entrada, '\n');
        entrada=getCurrentTimeNow();
        prestamos.setFecha(entrada);
        
        entrada=CurrentlyLoggedUser::g_userID();
        prestamos.setLaboratorista(entrada);
        entrada=randomNumberGenerator();
        prestamos.setId(entrada);
        
        do{
            entrada="";
            cout<<"\tIngrese la clave del material prestado: ";
            
            //cin.ignore();
            
            cin>>entrada;
            material=entrada;
            
            if(findMaterialInDb(result, material)){
                materials.fromString(result); 
                // for(int i=0; i<materiales.size(); i++){
                //     if(materiales[i].substr(0,materiales[i].find(" "))==material){
                //         cantidad=stoi(materiales[i].substr(materiales[i].find(" "),materiales[i].length()));
                //         cantidad+=stoi(materials.getCanidadPrestada());
                //         if(cantidad>=stoi(materials.getCantidad())){
                //             cout<<"No hay suficiente material"<<endl;
                //             cout<<"Desea continuar? (s/n): ";
                //             cin>>correcto;
                //             if(correcto=='s' || correcto == 'S'){
                //                 enough=false;
                //                 break;
                //             }else{
                //                 return;
                //             }
                //         }
                //     }
                // }
            }else{
                cout<<"El material no existe"<<endl;
                cout<<"Desea continuar? (s/n): ";
                cin>>correcto;
                if(correcto=='s' || correcto == 'S'){
                    continue;
                }else{
                    break;
                }
            }
            // if(enough){
            //     enough=true;
            //     break;
            // }
            cout<<"\tIngrese la cantidad prestada: ";
            cin>>entrada;
            cantidad=0;
            //materials.show(true);
            
            cantidad=stoi(materials.getCantidad());
            cantidad-=stoi(materials.getCanidadPrestada());
            //cout<<cantidad<<endl;
            if(stoi(entrada)>cantidad){
                cout<<"No hay suficiente material"<<endl;
                cout<<"Desea continuar? (s/n): ";
                cin>>correcto;
                if(correcto=='s' || correcto == 'S'){
                    continue;
                }else{
                    return;
                }
            }
            material+=" "+entrada;
            materiales.push_back(material);
            cout<<"Desea continuar? (s/n): ";
            cin>>correcto;
        }while(correcto=='s' || correcto == 'S');
        cin.clear();
        cin.ignore();
        fflush(stdin);
        prestamos.setMateriales(materiales);
        //Buscar expediente del us
        expediente=prestamos.getUsuario();
        entrada="Pendiente de devolucion";
        prestamos.setEstado(entrada);
        if(!findUserInDb(result, expediente)){
            cout<<"El usuario no existe"<<endl;
            system("pause");
            return;
        }
        prestamos.show();
        cout<<"Desea guardar el prestamo? (s/n): ";
        cin>>correcto;
        if(correcto=='s' || correcto == 'S'){
            ofstream archivo;
            archivo.open(BORROW_TABLE_NAME, ios::app);
            archivo<<prestamos.to_string();
            archivo.close();
            
            entrada=prestamos.getUsuario();
            MemPrestamos.setUsuario(entrada);
            entrada=prestamos.getFecha();
            MemPrestamos.setFecha(entrada);
            entrada=prestamos.getLaboratorista();
            MemPrestamos.setLaboratorista(entrada);
            entrada=prestamos.getId();
            MemPrestamos.setId(entrada);
            entrada="Pendiente de devolucion";
            MemPrestamos.setEstado(entrada); 
            prestamosInMemory.push_back(MemPrestamos);
            archivo.open(LEND_TABLE_NAME, ios::app);
            archivo<<MemPrestamos.to_string();
            archivo.close();
            system("pause");
            
            for(int i=0; i<prestamos.getMateriales().size(); i++){
                otra3=prestamos.getMateriales()[i];
                entrada=otra3.substr(0, otra3.find(" "));
                otra=otra3.substr(otra3.find(" ") + 1, otra3.length());
                if(findMaterialInDb(result, entrada)){
                    otra2=result;
                    materials.fromString(result); 
                    cantidad=stoi(materials.getCanidadPrestada());
                    cantidad+=stoi(otra);
                    materials.setCanidadPrestada(to_string(cantidad));
                    otra=materials.toString();
                    updateLine(MATERIALS_TABLE_NAME, otra2, otra);
                }
                
                
            }
            return;
        }else{
            return;
        }
        
    
    }while(correcto!='s' || correcto!='S');
}

void consultarPrestamosPendientes(vector<MemPrestamos> &prestamosInMemory){
    if(prestamosInMemory.size()==0){
        cout<<"No hay prestamos pendientes"<<endl;
        system("pause");
        return;
    }
    for(int i=0; i<prestamosInMemory.size(); i++){
        cout<<"------------Prestamo "<<i+1<<"------------"<<endl;
        if(prestamosInMemory[i].getEstado()=="Pendiente de devolucion"){
            prestamosInMemory[i].show();
        }
    }
    system("pause");
    return;
}

void devolver(vector<MemPrestamos> &prestamosInMemory){
    Prestamos prestamos;
    MemPrestamos MemPrestamos;
    vector<string> materiales;
    vector<string> newFileMaterials;
    Materials materials;
    string result;
    int cantidad=0;
    int id=-1;
    fflush(stdin);
    cin.clear();
    cin.ignore();
    string material;
    string entrada,expediente,otra,otra2,otra3,otra4;
    char correcto='s';
    do{
        system("cls");
        consultarPrestamosPendientes(prestamosInMemory);
        //cout<<"Intruzca el ID del prestamo que desea devolver"<<endl;
        cout<<"DEVOLUCION"<<endl;
        
        cout<<"\tIngrese el ID del prestamo: ";
        getline(cin, entrada, '\n');
        for(int i=0; i<prestamosInMemory.size(); i++){
            if(prestamosInMemory[i].getId()==entrada){
                id=i;
                prestamosInMemory[i].show();
                cout<<"Desea continuar? (s/n): ";
                cin>>correcto;
                if(correcto=='s' || correcto == 'S'){
                    expediente=prestamosInMemory[i].getId();
                    break;
                }else{
                    return;
                }
            }
        }
        if(id==-1){
            cout<<"El prestamo no existe"<<endl;
            system("pause");
            return;
        }

        if(findPrestamoInDb(result, expediente)){
            prestamos.from_string(result);
            prestamos.show();
            cout<<"Desea continuar? (s/n): ";
            cin>>correcto;
            if(correcto=='s' || correcto == 'S'){
                otra4=prestamos.to_string();
                entrada=getCurrentTimeNow();
                prestamos.setFecha_devolucion(entrada);
                entrada="Devuelto";
                prestamos.setEstado(entrada);
                
                for(int i=0; i<prestamos.getMateriales().size(); i++){
                    otra3=prestamos.getMateriales()[i];
                    entrada=otra3.substr(0, otra3.find(" "));
                    otra=otra3.substr(otra3.find(" ") + 1, otra3.length());
                    if(findMaterialInDb(result, entrada)){
                        otra2=result;
                        materials.fromString(result); 
                        cantidad=stoi(materials.getCanidadPrestada());
                        cantidad-=stoi(otra);
                        materials.setCanidadPrestada(to_string(cantidad));
                        otra=materials.toString();
                        updateLine(MATERIALS_TABLE_NAME, otra2, otra);
                    }
                }
                entrada=prestamos.to_string();
                updateLineBorrow(BORROW_TABLE_NAME, otra4, entrada);
                entrada=prestamosInMemory[id].to_string();
                otra3="";
                updateLineBorrow(LEND_TABLE_NAME, entrada, otra3);
                prestamosInMemory.erase(prestamosInMemory.begin() + id);
                prestamosInMemory.shrink_to_fit();
                cout<<"devolucion exitosa"<<endl;
                system("pause");
                return;
            }else{
                return;
            }
        }
        
          
    }while(correcto!='s' || correcto!='S');
}
bool findPrestamoInDb(string &registro, string &expediente){
    ifstream file(BORROW_TABLE_NAME, ios::in);
    string line;
    Prestamos user;
    while (getline(file, line,'\n')) {
        //mas estricta la busqueda
        user.from_string(line);
        if(user.getId()==expediente){
            registro=line;
            return true;
        }
    }
    return false;
}