//
//  main.cpp
//  Abgabe A1
//
//  Created by Paul Wirkus on 28.10.20.
//
/*
#include <iostream> //Aufgabe 1
#include <cmath>
using std::cin;
using std::cout;
using std::sqrt;

int main() {
    cout << "Bitte geben Sie die Koeffizienten eines Polynoms zweiten Grades ein.\n" << "A: "; //Einlesen von A
    double A;
    cin >> A;
    if ( A == 0 )
    {
        cout << "Es wurde A=0 gesetzt. Abbruch.\n";
        return 0;
    }
    
    cout << "B: "; //Einlesen von B
    double B;
    cin >> B;
    
    cout << "C: "; //Einlesen von C
    double C;
    cin >> C;
    
    double u = -B/(2*A);
    double v = sqrt(B*B-4*A*C)/(2*A);
    
    if ( v != 0 ) //Untersuchung der Vielfachheit der NS
    {
        cout << "Das besagte Polynom hat zwei Nullstellen.\n" << "Nullstelle 1: " << u+v << "\n" << "Nullstelle 2: " << u-v << "\n";
    } else
    {
        cout << "Das besagt Polynom hat eine Nullstelle: " << u;
    }
    
    return 0;
}
*/
/*
#include <iostream> //Aufgabe 2
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::sqrt;

int main() {
    cout << "Bitte geben Sie die Koeffizienten eines Polynoms zweiten Grades ein.\n" << "A: "; //Einlesen von A
    double A;
    cin >> A;
    if ( A == 0 )
    {
        cout << "Es wurde A=0 gesetzt. Abbruch.\n";
        return 0;
    }
    
    cout << "B: "; //Einlesen von B
    double B;
    cin >> B;
    
    cout << "C: "; //Einlesen von C
    double C;
    cin >> C;
    
    if ( B*B-4*A*C < 0 ) //komplexer Fall
    {
        double u = -B/(2*A);
        double v = sqrt(-B*B+4*A*C)/(2*A); //Multiplikation des Radikanten mit -1
        cout << "Das besagte Polynom besitzt folgende (komplexe) Nullstellen:" << endl
        << "Nullstelle 1: " << u << " + " << v << "i" << endl
        << "Nullstelle 2: " << u << " - " << v << "i" << endl;
    } else //reeller Fall
    {
        double u = -B/(2*A);
        double v = sqrt(B*B-4*A*C)/(2*A);
    
        if ( v != 0 ) //Untersuchung der Vielfachheit der NS
            {
                cout << "Das besagte Polynom hat zwei Nullstellen.\n" << "Nullstelle 1: " << u+v << "\n" << "Nullstelle 2: " << u-v << "\n";
            } else
            {
        cout << "Das besagte Polynom hat eine Nullstelle: " << u;
            }
    }
    return 0;
}
*/
/*
#include <iostream> //Aufgabe 2/3/1*
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::sqrt;
using std::string;

int main() {
    cout << "Bitte geben Sie die Koeffizienten eines Polynoms maximal zweiten Grades ein.\n" << "A: "; //Einlesen von A
    double A;
    cin >> A;
    
    cout << "B: "; //Einlesen von B
    double B;
    cin >> B;
    
    cout << "C: "; //Einlesen von C
    double C;
    cin >> C;
    
    if ( A == 0 )
    {
        if ( B == 0 )
        {
            if ( C == 0)
            {
                cout << "Es wurde die konstante Nullfunktion eingegeben, somit ist jedes x  eine Nullstelle.";
            } else
                cout << "Die eingegebene konstante Funktion besitzt keine Nullstellen.";
        }
        cout << "Das Polynom ersten Grades besitzt eine Nullstelle bei " << -C/B << "." << endl;
        return 0;
    }
    
    if ( B*B-4*A*C < 0 )
    {
        double u = -B/(2*A);
        double v = sqrt(-B*B+4*A*C)/(2*A);
        cout << "Das besagte Polynom besitzt folgende (komplexe) Nullstellen:" << endl
        << "Nullstelle 1: " << u << " + " << v << "i" << endl
        << "Nullstelle 2: " << u << " - " << v << "i" << endl;
    } else
    {
        double u = -B/(2*A);
        double v = sqrt(B*B-4*A*C)/(2*A);
    
        if ( v != 0 ) //Untersuchung der Vielfachheit der NS
            {
                cout << "Das besagte Polynom hat zwei Nullstellen.\n" << "Nullstelle 1: " << u+v << "\n" << "Nullstelle 2: " << u-v << "\n";
            } else
            {
        cout << "Das besagte Polynom hat eine Nullstelle: " << u << endl;
            }
    }
    string artex;
    if ( A > 0 )
        artex = "Minimum";
    else
        artex = "Maximum";
    double fval = A*-(B/(2*A))*-(B/(2*A))+B*-(B/(2*A))+C;
    cout << "Das Polynom besitzt eine Extremalstelle bei x = " << -(B/(2*A)) << "." << endl <<
    "Hierbei handelt es sich um ein " << artex << " mit dem Funktionswert " << fval << "." << endl;
    return 0;
}
*/

#include <iostream>
#include <complex>
typedef std::complex <double > Complex;
#include <cmath>
using namespace std;
int main() {
    double N1, N2, lkoef;
    cout << "Geben Sie die erste Nullstelle ein: ";
    cin >> N1;
    cout << "Geben Sie die zweite Nullstelle ein: ";
    cin >> N2;
    cout << "Geben Sie den Leitkoeffizienten ein: ";
    cin >> lkoef;
    cout << "Ihr Polynom ist:" << endl << lkoef << "x^2 + " << lkoef * (-N1 - N2) << "x + " << lkoef * N1 * N2 << endl;
    return 0;
}

