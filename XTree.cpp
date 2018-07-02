#include "stdafx.h"
#include "XTree.h"
#include <limits>
#include <algorithm>


XTree::XTree(int Dimensiones) {
    Dimensions = Dimensiones;
    M = 20;
    m = 10;
    Root = nullptr;
}

XTree::XTree() {
    Dimensions = 3;
    M = 4;
    m = 2;
    Root = nullptr;
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
            vector<double> DN (Dimensions);
            vector<double> DP (Dimensions);
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
    vector<int> seeds = PickSeeds(nodo->Hijos);
    vector<Nodo *> EntradasRestantes = nodo->Hijos;
    Nodo * G1 = nodo->Hijos[seeds[0]];
    Nodo * G2 = nodo->Hijos[seeds[1]];
    nodo->Hijos.clear();
    nodo->CalcularCoverage();
    Nodo * NN = new Nodo();
    NN->bHoja = nodo->bHoja;
    nodo->AddHijo(G1);
    NN->AddHijo(G2);
    NN->CalcularCoverage();
    EntradasRestantes.erase(find(EntradasRestantes.begin(), EntradasRestantes.end(), G1));
    EntradasRestantes.erase(find(EntradasRestantes.begin(), EntradasRestantes.end(), G2));
    while (!EntradasRestantes.empty()) {
        //falta un if aqui, segun el paper, es uno que conrtola que ambos grupos tenga el minimo
        int next = PickNext(EntradasRestantes, nodo, NN);
        Nodo * nodonext = EntradasRestantes[next];
        //ver que area crece mas
        vector<double> DN (Dimensions);
        vector<double> DP (Dimensions);
        ComponerRegion(nodo->PointN, nodo->PointP, nodonext->PointN, nodonext->PointP, DN, DP);
        double area1 = AreaRegion(DN, DP);
        double d1 = area1 - nodo->CoverageArea();
        ComponerRegion(NN->PointN, NN->PointP, nodonext->PointN, nodonext->PointP, DN, DP);
        double area2 = AreaRegion(DN, DP);
        double d2 = area2 - NN->CoverageArea();
        if (d1 < d2) {
            nodo->AddHijo(nodonext);
            nodo->CalcularCoverage();
        }
        else if (d2 < d1) {
            NN->AddHijo(nodonext);
            NN->CalcularCoverage();
        }
        else{
            if (area1 < area2) {
                nodo->AddHijo(nodonext);
                nodo->CalcularCoverage();
            }
            else {
                NN->AddHijo(nodonext);
                NN->CalcularCoverage();
            }
        }
        EntradasRestantes.erase(find(EntradasRestantes.begin(), EntradasRestantes.end(), nodonext));
    }
    return NN;
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
    //Nodo * N = ChooseLeaf(Data);//quiza deberia recibir Data para que ese chooseleaf trabaje con rectangulos no con punto
    Nodo * N = ChooseSubTree(Data);//quiza deberia recibir Data para que ese chooseleaf trabaje con rectangulos no con punto
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
    double dMax = 0;
    vector<double> JN (Dimensions);
    vector<double> JP (Dimensions);
    for (int i = 0; i < Entradas.size(); i++) {
        for (int j = i + 1; j < Entradas.size(); j++) {
            for (int k = 0; k < Dimensions; k++) {
                if (Entradas[i]->PointN[k] < Entradas[j]->PointN[k]) {
                    JN[k] = Entradas[i]->PointN[k];
                }
                else {
                    JN[k] = Entradas[j]->PointN[k];
                }
                if (Entradas[i]->PointP[k] > Entradas[j]->PointP[k]) {
                    JP[k] = Entradas[i]->PointP[k];
                }
                else {
                    JP[k] = Entradas[j]->PointP[k];
                }
            }
            //calculado J
            double areaJ = AreaRegion(JN, JP);
            double areaEI = Entradas[i]->CoverageArea();
            double areaEJ = Entradas[j]->CoverageArea();
            double d = areaJ - areaEI - areaEJ;
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
    vector<double> d1s(Entradas.size(), 0);
    vector<double> d2s(Entradas.size(), 0);
    int iMax = 0;
    double dMax = 0;
    for (int i = 0; i < Entradas.size(); i++) {
        vector<double> DN (Dimensions);
        vector<double> DP (Dimensions);
        ComponerRegion(G1->PointN, G1->PointP, Entradas[i]->PointN, Entradas[i]->PointP, DN, DP);
        double d1 = AreaRegion(DN, DP) - G1->CoverageArea();
        ComponerRegion(G2->PointN, G2->PointP, Entradas[i]->PointN, Entradas[i]->PointP, DN, DP);
        double d2 = AreaRegion(DN, DP) - G2->CoverageArea();
        double d = abs(d1 - d2);
        if (d > dMax) {
            dMax = d;
            iMax = i;
        }
    }
    return iMax;//retornar el i con la diferencia maxima, ese es el indicie de las entradas que debo escoger como siguiente
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

double XTree::OverlapRegions(vector<double>& N1, vector<double>& P1, vector<double>& N2, vector<double>& P2) {
    double acum = 1;
    for (int i = 0; acum && i < Dimensions; i++) {
        double sobreposicion = min(P1[i], P2[i]) - max(N1[i], N2[i]);
        if (sobreposicion <= 0) {
            acum *= 0;
        }
        else {
            acum *= sobreposicion;
        }
    }
    return acum;
}

double XTree::Margen(vector<double>& N, vector<double>& P) {
    double acum = 0.0;
    for (int i = 0; i < Dimensions; i++) {
        acum += P[i] - N[i];
    }
    return acum;
}

void XTree::Imprimir() {
    Root->Imprimir(0);
}

string XTree::Identacion(int Tam) {
    return string(Tam * 4, ' ');
}

Nodo * XTree::ChooseSubTree(Nodo * Data) {//no se que hace esto
    //hay una obtimizacon de esto, implementarla
    Nodo * N = Root;
    while (N->bHoja){
        if (N->Hijos.size()) {//este if es por segurida, debo asegurarme que tiene hijos
            int iMin = numeric_limits<int>::max();//
            if (N->Hijos.size() && N->Hijos[0]->bHoja) {//determine the minimun overlap cost
                double enlargeMin = numeric_limits<double>::max();
                double areaMin = numeric_limits<double>::max();
                double overlapMin = numeric_limits<double>::max();

                for (int i = 0; i < N->Hijos.size(); i++) {
                    //ver que overlap crece menos
                    vector<double> DN(Dimensions);
                    vector<double> DP(Dimensions);
                    ComponerRegion(N->Hijos[i]->PointN, N->Hijos[i]->PointP, Data->PointN, Data->PointP, DN, DP);
                    //calcular el overlap de esta nueva region, es decir sumar el overlap de esta region con los demas hijos del nodo N, no con respecto a este hijo i, no tendria sentido
                    double overlap = 0;
                    for (int j = 0; j < N->Hijos.size(); j++) {
                        if (j != i) {
                            overlap += OverlapRegions(DN, DP, N->Hijos[j]->PointN, N->Hijos[j]->PointP);
                        }
                    }
                    double area = AreaRegion(DN, DP);
                    double enlarge = area - N->Hijos[i]->CoverageArea();
                    if (overlap < overlapMin) {
                        iMin = i;
                        overlap = overlapMin;
                    }
                    else if (overlap == overlapMin) {
                        if (enlarge < enlargeMin) {
                            iMin = i;
                            enlargeMin = enlarge;
                            areaMin = area;
                        }
                        else if (enlarge == enlargeMin) {
                            if (area < areaMin) {
                                iMin = i;
                                enlargeMin = enlarge;
                                areaMin = area;
                            }
                        }
                    }
                }
            }
            else {//los hijos no apuntan a hojas
                double enlargeMin = numeric_limits<double>::max();
                double areaMin = numeric_limits<double>::max();

                for (int i = 0; i < N->Hijos.size(); i++) {
                    //ver que overlap crece menos
                    vector<double> DN(Dimensions);
                    vector<double> DP(Dimensions);
                    ComponerRegion(N->Hijos[i]->PointN, N->Hijos[i]->PointP, Data->PointN, Data->PointP, DN, DP);
                    //calcular el overlap de esta nueva region, es decir sumar el overlap de esta region con los demas hijos del nodo N, no con respecto a este hijo i, no tendria sentido
                    double area = AreaRegion(DN, DP);
                    double enlarge = area - N->Hijos[i]->CoverageArea();
                    if (enlarge < enlargeMin) {
                        iMin = i;
                        enlargeMin = enlarge;
                        areaMin = area;
                    }
                    else if (enlarge == enlargeMin) {
                        if (area < areaMin) {
                            iMin = i;
                            enlargeMin = enlarge;
                            areaMin = area;
                        }
                    }
                }
            }
            N = N->Hijos[iMin];
        }
    }
    return N;
}

int XTree::ChooseSplitAxis(Nodo * nodo) {//esta funcion en realida puede hacer split axis y split index a la vez, solo deberian retornar ambos indices
    //podria retornar el indicde del axis, en el compare axxis, y que esta funcion retorne el indice con el que se parte en dos las entradas.
    //asi en la fucnion split, llamo a esta funcon, obtengo los indices, y reconstruyo esa distribucion.
    vector<Nodo *> EntradasN = nodo->Hijos;
    vector<Nodo *> EntradasP = nodo->Hijos;
    for (int i = 0; i < Dimensions; i++) {
        CompareAxis = i;
        sort(EntradasN.begin(), EntradasN.end(), XTree::CompareEntriesByAxisLower);
        sort(EntradasP.begin(), EntradasP.end(), XTree::CompareEntriesByAxisUpper);
    }
    return 0;
}

bool XTree::CompareEntriesByAxisLower(Nodo * n1, Nodo * n2) {
    return n1->PointN[CompareAxis] < n2->PointN[CompareAxis];
}
bool XTree::CompareEntriesByAxisUpper(Nodo * n1, Nodo * n2) {
    return n1->PointP[CompareAxis] < n2->PointP[CompareAxis];
}
