//Código para el manejo de los laboratoristas
#include "lab.hpp"

string passWordCipher(string &passWord){
    string passWordCipher = "";
    for(int i = 0; i < passWord.length(); i++){
        passWordCipher += passWord[i];
        passWordCipher[i]=passWordCipher[i] + 3;
        //Aplicar operacion NOT
        passWordCipher[i] = ~passWordCipher[i];
        //Aplicar la operacion OR respecto al caracter original
        passWordCipher[i] = passWordCipher[i] | passWord[i];
        passWordCipher[i] = passWordCipher[i] ^ passWord[i];
        passWordCipher[i] = passWordCipher[i] & passWord[i];
    }
    return passWordCipher;
}

bool verifyPassword(string &passWord, string &passWordCiphered){
    if(passWordCiphered == passWordCipher(passWord)){
        return true;
    }
    return false;
}