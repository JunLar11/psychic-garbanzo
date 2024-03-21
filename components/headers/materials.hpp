#pragma once 
#include "prjheaders.hpp"
#include "helpers.hpp"
#define MATERIALS_TABLE_NAME "17032024177898.txt"

struct Materials{
    //Definicion y declaracion de las variables y metodos
    private:
        string id;
        string nombre;
        string descripcion;
        string cantidad;
        string cantidadPrestada;
    public:
    //Metodos
    void setId(string id){
        this->id = id;
    }
    void setNombre(string nombre){
        this->nombre = nombre;
    }
    void setDescripcion(string descripcion){
        this->descripcion = descripcion;
    }
    void setCantidad(string cantidad){
        this->cantidad = cantidad;
    }
    void setCanidadPrestada(string cantidadPrestada){
        this->cantidadPrestada = cantidadPrestada;
    }
    string getId(){
        return this->id;
    }
    string getNombre(){
        return this->nombre;
    }
    string getDescripcion(){
        return this->descripcion;
    }
    string getCantidad(){
        return this->cantidad;
    }
    string getCanidadPrestada(){
        return this->cantidadPrestada;
    }
    void fromString(string &registro){
        stringstream ss;
        ss<<registro;
        getline(ss, this->id, ',');
        getline(ss, this->nombre, ',');
        getline(ss, this->descripcion, ',');
        getline(ss, this->cantidad, ',');
        getline(ss, this->cantidadPrestada, ';');
    }
    //Constructor
    Materials(string id, string nombre, string descripcion, string cantidad, string canidadPrestada){
        this->id = id;
        this->nombre = nombre;
        this->descripcion = descripcion;
        this->cantidad = cantidad;
        this->cantidadPrestada = "0";
    }
    Materials(){
        this->id = "";
        this->nombre = "";
        this->descripcion = "";
        this->cantidad = "";
        this->cantidadPrestada = "0";
    }
    Materials(string &result){
        fromString(result);
    }
    string toString(){
        stringstream ss;
        ss<<this->id<<","<<this->nombre<<","<<this->descripcion<<","<<this->cantidad<<","<<this->cantidadPrestada<<";"<<endl;
        return ss.str();
    }
    void show(bool showShared=false){
        cout<<"ID: "<<this->id<<endl;
        cout<<"Nombre: "<<this->nombre<<endl;
        cout<<"Descripcion: "<<this->descripcion<<endl;
        cout<<"Cantidad: "<<this->cantidad<<endl;
        if(showShared){
            cout<<"Cantidad Prestada: "<<this->cantidadPrestada<<endl;
        }
    }

};

void addMaterial();

bool findMaterialInDb(string &registro, string &expediente);

void updateMaterial();

void deleteMaterial();

void getAllMaterials();
void getAMaterial();

