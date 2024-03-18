#include "headers/helpers.hpp"

string exePathGetter(){
    char path[MAX_PATH];
    if (GetModuleFileName(NULL, path, MAX_PATH) == 0) {
        cerr << "Error al obtener la ubicación del archivo exe\n";
        exit(1);
    }
    string pathStr = path;
    size_t pos = pathStr.find_last_of("\\/");
    if (pos != string::npos) {
        pathStr = pathStr.substr(0, pos);
    }

    return pathStr+"\\";
}

void updateLine(string filename, string &searchText, string &newLine) {
    ifstream inFile(filename, ios::in);
    vector<string> lines;
    string line;

    // Lee todas las líneas del archivo
    while (getline(inFile, line)) {
        // Si la línea contiene el texto de búsqueda, la actualiza
        if (line.find(searchText) != string::npos) {
            line = newLine;
        }
        lines.push_back(line);
    }

    inFile.close();

    // Escribe las líneas de nuevo al archivo
    ofstream outFile(filename);
    for (const auto &line : lines) {
        outFile << line << endl;
    }

    outFile.close();
}

void creadorArchivos(string fileName){
    string path = exePathGetter();

    string archivoTexto = path + fileName;

    ifstream archivoExistente(archivoTexto.c_str());
    if (archivoExistente) {
        return;
    }

    ofstream archivo(archivoTexto.c_str());
    if (!archivo) {
        cerr << "ERROR: NO SE HA PODIDO CREAR EL ARCHIVO "<< archivoTexto << ">" << endl;
        cout<<  "Finalizando el programa..." << endl;
        system("pause");
        exit(1);
    }
    
    archivo.close();

    return;
}

