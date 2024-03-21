#pragma once 
#include "prjheaders.hpp"
#define SUPERUSER "13032024"
#define SUPERPASS "SPadBal2024"


/**
 * @struct CurrentlyLoggedUser
 * @brief Una estructura para representar al usuario actualmente conectado.
 * 
 * Esta estructura contiene miembros estáticos para mantener el ID del usuario, el nivel de acceso y el estado de conexión.
 * Proporciona métodos getter y setter estáticos para estos miembros.
 */
struct CurrentlyLoggedUser {

    
private:
    static string userID; ///< El ID del usuario actualmente conectado.
    static bool userAccessLevel; ///< El nivel de acceso del usuario actualmente conectado. Verdadero para acceso de alto nivel, falso para acceso de bajo nivel.
    static bool logged; ///< El estado de conexión del usuario. Verdadero si el usuario está conectado, falso de lo contrario.
    static string name; ///< El nombre del usuario actualmente conectado.
public:
    
    /**
     * @brief Obtener el ID del usuario
     * 
     * @return string El ID del usuario actualmente conectado.
     */
    static string g_userID() {
        return CurrentlyLoggedUser::userID;
    }

    /**
     * @brief Establecer el ID del usuario
     * 
     * @param _userID El nuevo ID de usuario a establecer.
     */
    static void s_userID(string _userID) {
        CurrentlyLoggedUser::userID = _userID;
    }

    /**
     * @brief Obtener el nivel de acceso del usuario
     * 
     * @return bool El nivel de acceso del usuario actualmente conectado.
     */
    static bool g_userAccessLevel() {
        return CurrentlyLoggedUser::userAccessLevel;
    }

    /**
     * @brief Establecer el nivel de acceso del usuario
     * 
     * @param _userAccessLevel El nuevo nivel de acceso a establecer. Verdadero para acceso de alto nivel, falso para acceso de bajo nivel.
     */
    static void s_userAccessLevel(bool _userAccessLevel) {
        CurrentlyLoggedUser::userAccessLevel = _userAccessLevel;
    }

    /**
     * @brief Obtener el estado de conexión
     * 
     * @return bool El estado de conexión del usuario.
     */
    static bool g_logged() {
        return CurrentlyLoggedUser::logged;
    }

    /**
     * @brief Establecer el estado de conexión
     * 
     * @param _logged El nuevo estado de conexión a establecer. Verdadero si el usuario está conectado, falso de lo contrario.
     */
    static void s_logged(bool _logged) {
        CurrentlyLoggedUser::logged = _logged;
    }

    /**
     * @brief Obtener el nombre del usuario
     * 
     * @return string El nombre del usuario actualmente conectado.
     */
    static string g_name() {
        return CurrentlyLoggedUser::name;
    }
    
    /**
     * @brief Establecer el nombre del usuario
     * 
     * @param _name El nuevo nombre de usuario a establecer.
     */
    static void s_name(string _name) {
        CurrentlyLoggedUser::name = _name;
    }

    //Métodos
    private:
    static void setSession(string _name, bool _logged, string _uID, bool _accessLevel=false){
        CurrentlyLoggedUser::name = _name;
        CurrentlyLoggedUser::logged = _logged;
        CurrentlyLoggedUser::userID = _uID;
        CurrentlyLoggedUser::userAccessLevel = _accessLevel;
    }

    public:
    static void login(string _name, bool _logged, string _uID, bool _accessLevel=false){
        setSession(_name, _logged, _uID, _accessLevel);
    }

    static void logout(){
        setSession("", false, 0,false);
    }


}; ///< Una instancia de la estructura CurrentlyLoggedUser para representar al usuario actualmente conectado.
