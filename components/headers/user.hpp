#pragma once 
#include "prjheaders.hpp"
#include "helpers.hpp"
#define USERS_TABLE_NAME "17032024035734.txt"
struct User{
    private:
        string expediente;
        string nombre;
        string correo;
        string telefono;
        string carrera;

    public:
    User(){
        this->expediente = "";
        this->nombre = "";
        this->correo = "";
        this->telefono = "";
        this->carrera = "";
    }
    User(int expediente, string nombre, string correo, string telefono, string carrera){
        this->expediente = expediente;
        this->nombre = nombre;
        this->correo = correo;
        this->telefono = telefono;
        this->carrera = carrera;
    }
    User(string &registro){
        setFromString(registro);

    }

    string getExpediente(){
        return this->expediente;
    }
    string getNombre(){
        return this->nombre;
    }
    string getCorreo(){
        return this->correo;
    }
    string getTelefono(){
        return this->telefono;
    }
    string getCarrera(){
        return this->carrera;
    }

    void setExpediente(string expediente){
        this->expediente = expediente;
    }
    void setNombre(string nombre){
        this->nombre = nombre;
    }
    void setCorreo(string correo){
        this->correo = correo;
    }
    void setTelefono(string telefono){
        this->telefono = telefono;
    }
    void setCarrera(string carrera){
        this->carrera = carrera;
    }

    void setFromString(string &registro){
        stringstream ss(registro);
        string nombre, correo, telefono, carrera, expediente;
        getline(ss, expediente, ',');
        getline(ss, nombre, ',');
        getline(ss, correo, ',');
        getline(ss, telefono, ',');
        getline(ss, carrera, ';');
        this->expediente = expediente;
        this->nombre = nombre;
        this->correo = correo;
        this->telefono = telefono;
        this->carrera = carrera;
    }

    void show(){

        cout<<"\tExpediente: "<<this->expediente<<endl;
        cout<<"\tNombre: "<<this->nombre<<endl;
        cout<<"\tCorreo: "<<this->correo<<endl;
        cout<<"\tTelefono: "<<this->telefono<<endl;
        cout<<"\tCarrera: "<<this->carrera<<endl;
    }

    string toString(){
        stringstream ss;
        ss<<this->expediente<<","<<this->nombre<<","<<this->correo<<","<<this->telefono<<","<<this->carrera<<";"<<endl;
        return ss.str();
    }

};

User addUser();

bool findUserInDb(string &registro, string &expediente);

User updateUser();