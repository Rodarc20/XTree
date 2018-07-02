#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
class LectorArchivos {
    public:
        vector<vector<double> > ObtenerPuntos();
        LectorArchivos();
        ~LectorArchivos();
};

