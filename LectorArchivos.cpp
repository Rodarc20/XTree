#include "stdafx.h"
#include "LectorArchivos.h"


vector<vector<double>> LectorArchivos::ObtenerPuntos() {
    vector<vector<double> > res;
    std::string line;
    //std::ifstream myfile ("./country-capitals.csv");
    //std::ifstream myfile ("./crime50k3.csv");
    std::ifstream myfile ("D:/UCSP/EDA/DataSets/YearPredictionMSD/YearPredictionMSD.txt");
    //std::ifstream myfile ("D:/UCSP/TareasUCSP_ws/TareasUCSP/EDA/QuadTreeVisualization/crime50k3.csv");
    //archivos de prueba, esot no requiere la covnersion posterior a
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            //cout << line << endl;
            vector<string> split;
            int inicio = 0;
            for(int i = 0; i < line.length(); i++){
                if(line[i] == ','){
                    //cout << "i: " << i << " stringanterior: " << line.substr(inicio, i-1 - inicio + 1) << endl;
                    split.push_back(line.substr(inicio, i-1 - inicio + 1));
                    //cout << split[split.size()-1] << endl;
                    inicio = i+1;
                }
            }
            split.push_back(line.substr(inicio));
            //a linde debo dividirlo en comas
            //se sumpne que split debe tener tamañó 5 siempre;
            vector<double> p (split.size());
            for (int j = 0; j < split.size() - 1; j++) {
                p[j] = stof(split[j]);
            }
            res.push_back(p);
        }
        myfile.close();
    }
    return res;
}

LectorArchivos::LectorArchivos() {
}


LectorArchivos::~LectorArchivos() {
}
