//Programa para la administración de el laboratorio de automatización
/*
El programa debe de estar hecho con estructuras y vectores.
Se van a crear cuatro estructuras:
-Laboratorista
   >Nombre
   >userID
   >Correo
   >Telefono
   >Turno
-Material
   >ID
   >Nombre
   >Cantidad
   >Ubicación
   >Descripción
-Préstamo
   >ID
   >Materiales
   >Materia
   >Fecha préstamos
   >Fecha de devolución
   >Observaciones
   >Laboratorista
-Usuario
   >Expediente
   >Nombre
   >Correo
   >Telefono
   >Carrera
*/

#include "components/headers/menus.hpp"
#include "components/headers/sessions.hpp"



using namespace std;






int main() {
   bool remainInProgram=false;
    setlocale(LC_CTYPE, "spanish");
    locale::global(locale("es_ES.utf8"));
    //Creando los archivos de texto necesarios
    creadorArchivos(LAB_TABLE_NAME);
    creadorArchivos(MATERIALS_TABLE_NAME);
    creadorArchivos(BORROW_TABLE_NAME);
    creadorArchivos(USERS_TABLE_NAME);

    // Obtener el manejador de la ventana de consola
    HWND hwnd = GetConsoleWindow();

    // Establecer el ícono de la ventana de consola
    // HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    // SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    // SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    SetConsoleTitleA("Administrador");

    // Mostrar la ventana de consola en la barra de tareas
    ShowWindow(hwnd, SW_SHOW);

    do{
      if(!CurrentlyLoggedUser::g_logged()){
         login();
      }
      if(CurrentlyLoggedUser::g_logged()){
         remainInProgram=mainMenu();
      }
      if(!remainInProgram){
         CurrentlyLoggedUser::logout();
      }
      system("cls");
    }while(remainInProgram);
    cout<<"PROGRAMA FINALIZADO CON EXITO"<<endl;
    system("pause");
    exit(0);
    return 0;
}

