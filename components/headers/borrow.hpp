#pragma once 
#include "prjheaders.hpp"
#define BORROW_TABLE_NAME "17032024973867.txt"
#define LEND_TABLE_NAME "17032034973868.txt"



struct Prestamos{ 
    private: 
        string id;
        vector<string> materiales;
        string fecha;
        string laboratorista;
        string usuario;
        string estado;
        string observaciones;
        string fecha_devolucion;


    public:
    Prestamos(){
        this->id = "";
        this->materiales = vector<string>();
        this->fecha = "";
        this->laboratorista = "";
        this->usuario = "";
        this->estado = "";
        this->observaciones = "";
        this->fecha_devolucion = "";
    }
    Prestamos(string &id, vector<string> &materiales, string &fecha, string &laboratorista, string &usuario, string &estado, string &observaciones, string &fecha_devolucion){
        this->id = id;
        this->materiales = materiales;
        this->fecha = fecha;
        this->laboratorista = laboratorista;
        this->usuario = usuario;
        this->estado = estado;
        this->observaciones = observaciones;
        this->fecha_devolucion = fecha_devolucion;
    }
    Prestamos(string &registro){

        this->from_string(registro);
    }

    string getId(){
        return this->id;
    }
    void setId(string &id){
        this->id = id;
    }

    void setMateriales(vector<string> &materiales){
        this->materiales = materiales;
    }
    vector<string> getMateriales(){
        return this->materiales;
    }

    string getFecha(){
        return this->fecha;
    }
    void setFecha(string &fecha){
        this->fecha = fecha;
    }
    
    string getLaboratorista(){
        return this->laboratorista;
    }
    void setLaboratorista(string &laboratorista){
        this->laboratorista = laboratorista;
    }
    
    string getUsuario(){
        return this->usuario;
    }
    void setUsuario(string &usuario){
        this->usuario = usuario;
    }
    
    string getEstado(){
        return this->estado;
    }
    void setEstado(string &estado){
        this->estado = estado;
    }
    
    string getObservaciones(){
        return this->observaciones;
    }
    void setObservaciones(string &observaciones){
        this->observaciones = observaciones;
    }

    string getFecha_devolucion(){
        return this->fecha_devolucion;
    }
    void setFecha_devolucion(string &fecha_devolucion){
        this->fecha_devolucion = fecha_devolucion;
    }
    
    string to_string(){
        string material = "";
        stringstream ss;
        for(int i = 0; i < this->materiales.size(); i++){
            material+=this->materiales[i]+"|";
        }
        ss << this->id << "," << material << "," << this->fecha << "," << this->laboratorista << "," << this->usuario << "," << this->estado << "," << this->observaciones << "," << this->fecha_devolucion << ";"<< endl;
        //cout<<ss.str()<<endl;
        return ss.str();

    }
    void from_string(string &registro){
        stringstream ss;
        ss<<registro;
        getline(ss, this->id, ',');
        string materiales = "";
        string material = "";
        getline(ss, materiales, ',');
        stringstream ss2;
        ss2<<materiales;
        while(getline(ss2, material, '|')){
            this->materiales.push_back(material);
        }

        getline(ss, this->fecha, ',');
        getline(ss, this->laboratorista, ',');
        getline(ss, this->usuario, ',');
        getline(ss, this->estado, ',');
        getline(ss, this->observaciones, ',');
        getline(ss, this->fecha_devolucion, ';');
    }
    void show(){
        cout<<"ID: "<<this->id<<endl;
        cout<<"Materiales: "<<endl;
        for(int i = 0; i < this->materiales.size(); i++){
            //Imprimir clave y cantidad
            cout<<"\t"<<i+1<<" - Clave: "<<this->materiales[i].substr(0, this->materiales[i].find(" "));
            cout<<" - Cantidad: "<<this->materiales[i].substr(this->materiales[i].find(" ") + 1, this->materiales[i].size())<<endl;
        }
        cout<<"Fecha: "<<this->fecha<<endl;
        cout<<"Laboratorista: "<<this->laboratorista<<endl;
        cout<<"Usuario: "<<this->usuario<<endl;
        cout<<"Estado: "<<this->estado<<endl;
        cout<<"Observaciones: "<<this->observaciones<<endl;
    }

};

struct MemPrestamos{
    //Estructura mas pequeña, representa un prestamo en memoria
    private:
        string id;
        string fecha;
        string laboratorista;
        string usuario;
        string estado;
    
    public:
    MemPrestamos(){
        this->id = "";
        this->fecha = "";
        this->laboratorista = "";
        this->usuario = "";
        this->estado = "";
    }
    MemPrestamos(string &id, string &fecha, string &laboratorista, string &usuario, string &estado){
        this->id = id;
        this->fecha = fecha;
        this->laboratorista = laboratorista;
        this->usuario = usuario;
        this->estado = estado;
    }
    MemPrestamos(string &registro){
        from_string(registro);
    }
    
    string getId(){
        return this->id;
    }
    void setId(string &id){
        this->id = id;
    }
    
    string getFecha(){
        return this->fecha;
    }
    void setFecha(string &fecha){
        this->fecha = fecha;
    }
    
    string getLaboratorista(){
        return this->laboratorista;
    }
    void setLaboratorista(string &laboratorista){
        this->laboratorista = laboratorista;
    }
    
    string getUsuario(){
        return this->usuario;
    }
    void setUsuario(string &usuario){
        this->usuario = usuario;
    }
    
    string getEstado(){
        return this->estado;
    }
    void setEstado(string &estado){
        this->estado = estado;
    }
    
    string to_string(){
        stringstream ss;
        ss << this->id << "," << this->fecha << "," << this->laboratorista << "," << this->usuario << "," << this->estado << ";"<< endl;
        return ss.str();
        //return this->id+","+this->fecha+","+this->laboratorista+","+this->usuario+","+this->estado+";\n";
    }
    void from_string(string &registro){
        stringstream ss;
        ss<<registro;
        getline(ss, this->id, ',');
        getline(ss, this->fecha, ',');
        getline(ss, this->laboratorista, ',');
        getline(ss, this->usuario, ',');
        getline(ss, this->estado, ';');
    }
    void show(){
        cout<<"ID: "<<this->id<<endl;
        cout<<"Fecha: "<<this->fecha<<endl;
        cout<<"Laboratorista: "<<this->laboratorista<<endl;
        cout<<"Usuario: "<<this->usuario<<endl;
        cout<<"Estado: "<<this->estado<<endl;
    }
        
}; 

void prestar(vector<MemPrestamos> &prestamosInMemory);

void devolver(vector<MemPrestamos> &prestamosInMemory);
void consultarPrestamosPendientes(vector<MemPrestamos> &prestamosInMemory);
bool findPrestamoInDb(string &registro, string &expediente); 