#include "stdafx.h"
#include "XTree.h"
#include <limits>


XTree::XTree(int Dimensiones) {
    Dimensions = Dimensiones;
    M = 5;
    m = 2;
}

XTree::XTree() {
    Dimensions = 3;
    M = 5;
    m = 2;
}


XTree::~XTree() {
}

Nodo * XTree::ChooseLeaf(Nodo * Data) {
    Nodo * N = Root;
    //return nullptr;
    while (!N->bHoja) {
        //busco la entrada en la que al insertar se produzca el menor enlargement, en caso de empate, escober el rectangulo que de menor area
        //calrcular enlargement
        //calcular area
        //cambiar N por el nodo escogido, este sera el numeo N, repetir hasta que sea una hoja.
        //int iMin = 100000000;
        //double dMin = 100000000;//deberia ser el double maximo
        //double areaMin = 100000000;
        int iMin = numeric_limits<int>::max();
        double dMin = numeric_limits<double>::max();
        double areaMin = numeric_limits<double>::max();

        for (int i = 0; i < N->Hijos.size(); i++) {
            //ver que area crece mas
            vector<double> DN;
            vector<double> DP;
            ComponerRegion(N->Hijos[i]->PointN, N->Hijos[i]->PointP, Data->PointN, Data->PointP, DN, DP);
            double area = AreaRegion(DN, DP);
            double d = area - N->Hijos[i]->CoverageArea();
            if (d < dMin) {
                iMin = i;
                dMin = d;
                areaMin = area;
            }
            else if (d == dMin) {
                if (area < areaMin) {
                    iMin = i;
                    dMin = d;
                    areaMin = area;
                }
            }
        }
        N = N->Hijos[iMin];
    }
    return N;
}

Nodo * XTree::SplitNodo(Nodo * nodo) {
    return nullptr;
}

void XTree::Insert(vector<double> point) {
    Nodo * Data = new Nodo(point);
    if (Root == nullptr) {//caso base
        Root = new Nodo();
        Root->bHoja = true;
        Root->AddHijo(Data);
        AdjustTree(Root, nullptr);
        return;
    }
    Nodo * N = ChooseLeaf(Data);//quiza deberia recibir Data para que ese chooseleaf trabaje con rectangulos no con punto
    //add record to leaf
    if (N->Hijos.size() < M) {
        //insertar
        N->AddHijo(Data);//se entiende que n es una hoja
        AdjustTree(N, nullptr);
    }
    else {
        N->AddHijo(Data);//se entiende que n es una hoja
        Nodo * NN = SplitNodo(N);
        //inserta en N y NN

        AdjustTree(N, NN);
        //NN es unido al padre dengro de la funcion adjustTree
    }
    //Propagar el split si es necesario
}

void XTree::AdjustTree(Nodo * N, Nodo * NN) {
    //como esta funcion solo se llama al insertar un nuevo punto, y se llama despues de agregar un hijo a un nodo, puedo hacer aqui la actualizacion del overage, en lugar de la funcion addHijo
    //actualizar el covering rectangle
    N->CalcularCoverage();//hace lo que el for comentado
    if (Root == N) {//o si N no tiene padre
        if (NN) {//nuevonivel
            Root = new Nodo;
            Root->AddHijo(N);
            Root->AddHijo(NN);
            Root->CalcularCoverage();
        }
        return;
    }
    if (NN) {
        Nodo * P = N->Padre;
        if (P->Hijos.size() < M) {
            //insertar
            P->AddHijo(NN);
            AdjustTree(P, nullptr);
        }
        else {
            P->AddHijo(NN);
            Nodo * PP = SplitNodo(P);
            AdjustTree(P, PP);
            //y a donde debo unir NN?// lo unise al padre pero lo hace la funcion AdjustTree
        }
    }
    else{//no hubo un split en el hijo N
        Nodo * P = N->Padre;
        AdjustTree(P, nullptr);
    }
}

vector<int> XTree::PickSeeds(vector<Nodo*>& Entradas) {
    int iMax = 0;
    int jMax = 1;
    float dMax = 0;
    vector<double> JN;
    vector<double> JP;
    for (int i = 0; i < Entradas.size(); i++) {
        for (int j = i + 1; j < Entradas.size(); j++) {
            for (int k = 0; k < Dimensions; k++) {
                if (Entradas[i]->PointN[k] < Entradas[j]->PointN[k]) {
                    JN[i] = Entradas[i]->PointN[k];
                }
                else {
                    JN[i] = Entradas[j]->PointN[k];
                }
                if (Entradas[i]->PointP[k] > Entradas[j]->PointP[k]) {
                    JP[i] = Entradas[i]->PointP[k];
                }
                else {
                    JP[i] = Entradas[j]->PointP[k];
                }
            }
            //calculado J
            float areaJ = AreaRegion(JN, JP);
            float areaEI = Entradas[i]->CoverageArea();
            float areaEJ = Entradas[j]->CoverageArea();
            float d = areaJ - areaEI - areaEJ;
            if (d > dMax) {
                dMax = d;
                iMax = i;
                jMax = j;
            }
        }
    }
    vector<int>res;
    res.push_back(iMax);
    res.push_back(jMax);
    return res;
}

int XTree::PickNext(vector<Nodo*>& Entradas, Nodo * G1, Nodo * G2) {
    return 0;
}

void XTree::ComponerRegion(vector<double> & R1N, vector<double> & R1P, vector<double> & R2N, vector<double> & R2P, vector<double>& RN, vector<double>& RP) {//evitar recibir copias
    for (int i = 0; i < R1N.size(); i++) {
        if (R1N[i] < R2N[i]) {
            RN[i] = R1N[i];
        }
        else {
            RN[i] = R2N[i];
        }
        if (R1P[i] > R2P[i]) {
            RP[i] = R1P[i];
        }
        else {
            RP[i] = R2P[i];
        }
    }
}

double XTree::AreaRegion(vector<double> & N, vector<double> & P) {
    double acum = 1;
    for (int i = 0; i < N.size(); i++) {//pintLu tiene el mismo tamaño que potinRB y data point
        //tener cuidado con el sistema de coordenas, de pronto alguno tiene el ordn invertido, es decir Point LU podria estar en los negativos en un eje, pero podria estar en los positivos en otro eje, 
        //lo importante es que LU y RB son vertices opuestos del hypercubo, les cambiare el nombre
        acum *= P[i] - N[i];
    }
    return acum;
}

void XTree::Imprimir() {
    Root->Imprimir(0);
}

string XTree::Identacion(int Tam) {
    return string(Tam * 4, ' ');
}
