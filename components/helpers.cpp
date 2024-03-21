#include "headers/helpers.hpp"
#include "headers/borrow.hpp"

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
    while (getline(inFile, line, '\n')) {
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
void updateLineBorrow(string filename, string &searchText, string &newLine) {
    ifstream inFile(filename, ios::in);
    vector<string> lines;
    string line;
    // Lee todas las líneas del archivo
    while (getline(inFile, line)) {
        line+='\n';
        // Si la línea contiene el texto de búsqueda, la actualiza
        if (line.compare(searchText) == 0){
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

void deleteFromFile(string filename, string &searchText) {
    ifstream inFile(filename, ios::in);
    vector<string> lines;
    string line;

    // Lee todas las líneas del archivo
    while (getline(inFile, line)) {
        // Si la línea contiene el texto de búsqueda, la elimina
        if (line.find(searchText) == string::npos) {
            lines.push_back(line);
        }
    }

    inFile.close();

    // Escribe las líneas de nuevo al archivo
    ofstream outFile(filename,ios::out);
    for (const auto &line : lines) {
        outFile << line << endl;
    }

    outFile.close();
}

void getAllFromFile(string filename, vector<string> &allLines) {
    ifstream inFile(filename, ios::in);
    string line;

    // Lee todas las líneas del archivo
    while (getline(inFile, line)) {
        if(line.length() > 0){
            allLines.push_back(line);
        }
        
    }
    
    inFile.close();
}

string getCurrentTimeNow(){
    // Obtener la hora actual
    time_t t;
    tm tm;
    char buffer[20]; // Suficiente para almacenar la fecha formateada

    time(&t);
    localtime_s(&tm, &t);

    // Formatear la hora en el formato deseado
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &tm);
    string formattedTime(buffer);
    return formattedTime;
}

void loadInMemoryBorrows(vector<MemPrestamos> &allLines,string fileName) {

    ifstream inFile(fileName, ios::in);
    string line;
    MemPrestamos prestamo;
    // Lee todas las líneas del archivo
    while (getline(inFile, line)) {
        if(line.length() > 0){
        
            prestamo.from_string(line);
            allLines.push_back(prestamo);
        }
        
    }
    
    inFile.close();
    
}

string randomNumberGenerator(){
    srand(time(0));
    //Numero aleatorio entre 0 y 10000
    return to_string(rand()%10000);
}