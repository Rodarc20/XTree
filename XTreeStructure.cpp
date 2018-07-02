// XTreeStructure.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "XTree.h"
#include "Nodo.h"
#include "LectorArchivos.h"


void ManualTest() {
    int dimensiones;
    cout << "Numero de dimensiones: " << endl;
    cin >> dimensiones;
    XTree xt (dimensiones);
    int numeropuntos;
    cout << "Ingrese numero de puntos: " << endl;
    cin >> numeropuntos;
    while (numeropuntos) {
        vector<double> p (dimensiones);
        for (int i = 0; i < dimensiones; i++) {
            cin >> p[i];
        }
        cout << "insertando..." << endl;
        xt.Insert(p);
        xt.Imprimir();
        numeropuntos--;
    }
    cout << "fin de inserciones" << endl;
    getchar();
}

void YearPredictionTest() {
    XTree xt;
    LectorArchivos l;
    vector<vector<double> > puntos = l.ObtenerPuntos();
    cout << "puntos obtenidos: " << puntos.size() << endl;
    int count = 0;
    for(int i = 0; i < puntos.size(); i++){
        xt.Insert(puntos[i]);
        count++;
    }
    cout << "nodos insertados: " << count << endl;
    getchar();
    xt.Imprimir();
    getchar();
}

int main() {
    //ManualTest();
    YearPredictionTest();
    return 0;
}

