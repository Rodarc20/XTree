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
    cout << "punto para buscar" << endl;
    vector<double> p (dimensiones);
    for (int i = 0; i < dimensiones; i++) {
        cin >> p[i];
    }
    cout << "buscando..." << endl;
    cout << xt.Find(p) << endl;
    getchar();
    getchar();
    getchar();
    xt.Imprimir();
}

void ManualTestDistancia() {
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
    cout << "punto para range query" << endl;
    vector<double> p (dimensiones);
    for (int i = 0; i < dimensiones; i++) {
        cin >> p[i];
    }
    double distancia;
    cout << "rango: ";
    cin >> distancia;
    cout << "buscando..." << endl;
    vector<vector<double> > res = xt.Range(p, distancia);
    for (int j = 0; j < res.size(); j++) {
        cout << "Punto " << j << ": (";
        for (int i = 0; i < res[j].size()-1; i++) {
            cout << res[j][i] << ", ";
        }
        cout << res[j][res[j].size()-1] << ")" << endl;
    }
    getchar();
    getchar();
    getchar();
    //xt.Imprimir();

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
        if (!(count % 10)) {
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
    ManualTestDistancia();
    //YearPredictionTest();
    return 0;
}

