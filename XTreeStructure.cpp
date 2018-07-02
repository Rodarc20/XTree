// XTreeStructure.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "XTree.h"
#include "Nodo.h"


int main() {
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

    return 0;
}

