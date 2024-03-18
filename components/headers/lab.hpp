#pragma once 
#include "prjheaders.hpp"

#include "helpers.hpp"


#define LAB_TABLE_NAME "17032024034625.txt"


struct Laboratorista {
    private:
        string id;
        string nombre;
        string password;
        string telefono;
        string turno;
    public:
    //Constructor
    Laboratorista(string id, string nombre, string password, string telefono, string turno);
    Laboratorista(string &registro);
    Laboratorista();

    //Getters
    string getId();
    string getNombre();
    string getPassword();
    string getTelefono();
    string getTurno();
    //Setters
    void setId(string id);
    void setNombre(string nombre);
    void setPassword(string password);
    void setTelefono(string telefono);
    void setTurno(string turno);
    //Functions
    void getFromString(string &registro);
};




string passWordCipher(string &passWord);
bool verifyPassword(string &passWord, string &passWordCiphered);
void login();
void parseLaboratorista(string &line, Laboratorista &lab);
bool searchLaboratorista(string &labID, string &result);
void solicitarContrasena(string &password);