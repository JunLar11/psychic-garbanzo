#pragma once 
#include "prjheaders.hpp"
#include "helpers.hpp"
#define LAB_TABLE_NAME "17032024034625.txt"

string passWordCipher(string &passWord);
bool verifyPassword(string &passWord, string &passWordCiphered);
void login();