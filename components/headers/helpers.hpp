#pragma once 
#include "prjheaders.hpp"
#include "borrow.hpp"



string exePathGetter();
void creadorArchivos(string fileName);

void updateLine(string filename, string &searchText, string &newLine);
void deleteFromFile(string filename, string &searchText);
void getAllFromFile(string filename, vector<string> &allLines);

void loadInMemoryBorrows(vector<MemPrestamos> &allLines,string fileName);

string getCurrentTimeNow();

string randomNumberGenerator();

void updateLineBorrow(string filename, string &searchText, string &newLine);