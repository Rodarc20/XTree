// XTreeStructure.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ctime>
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
    unsigned t0,t1;
    LectorArchivos l;
    t0 = clock();
    vector<vector<double> > puntos = l.ObtenerPuntos();
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "puntos obtenidos: " << puntos.size() << endl;
    printf("Finalizado: %f\n", time);

    XTree xt (puntos[0].size());
    int count = 0;
    t0 = clock();
    for(int i = 0; i < puntos.size(); i++){
        xt.Insert(puntos[i]);
        count++;
        if (!(count % 1000)) {
            cout << count << " nodos insertados." << endl;
        }
    }
    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "nodos insertados: " << count << endl;
    printf("Finalizado: %f\n", time);
    getchar();
    xt.Imprimir();
    getchar();
}

int main() {
    //ManualTest();
    YearPredictionTest();
    return 0;
}

