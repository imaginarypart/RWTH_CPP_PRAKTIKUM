//
//  main.cpp
//  Aufgabe A1+
//
//  Created by Paul Wirkus on 06.11.20.
//

#include <iostream>
#include <cmath>
#include <algorithm>

double eTol( double X, double Xs ) //Berechnet Approximationsgüte
{
    double res = std::abs( X - Xs );
    return res;
}

int gcd ( int a, int b )
{
    if(b == 0)
        return a;
        else
        return gcd(b, a % b);
}

int main() {
    double X, Tol; //Einlesen von X und Tol
    std::cout << "Geben Sie eine reelle Zahl ein: ";
    std::cin >> X;
    std::cout << "Geben Sie die Toleranz für die Kettenbruchentwicklung ein: ";
    std::cin >> Tol;
    
    double Z_old, Z, Z_new, N_old, N, N_new, r; //Deklaration der benötigten Variablen
    Z_old = N = 1;
    N_old = 0;
    r = X;
    
    Z = std::round(r);
    
    while ( eTol(X, Z/N) > Tol )
    {
        r = 1/(r - std::round(r)); //r_k <- r_{k+1}
        std::cout << std::round(r) << std::endl; //Ausgabe a_k
        
        Z_new = std::round(r)*Z + Z_old; //Anwendung der Rekursionsvorschrift für Z_k
        Z_old = Z;
        Z = Z_new;
        
        N_new = std::round(r)*N + N_old; //Anwendung der Rekursionsvorschrift für N_k
        N_old = N;
        N = N_new;
    }
    int zngcd = gcd(Z, N);
    std::cout << Z/zngcd << " / " << N/zngcd << std::endl; //Ausgabe der Approximation
    return 0;
}
