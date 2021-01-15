//
//  Abgabe 2, C++-Praktikum
//
//
//
//

#include <iostream>
#include <cmath> //Für std::exp, std::sin

//Funktionsdeklarationen

double f ( double x ); //Implementiert die Funktion f. x
void Wertetabelle ( double a, double b, int N ); //Gibt Argument und Funktionswert tabellarisch aus. x
bool Einschluss ( double fa, double fb ); //Überprüft, ob die beiden Argumente unterschiedliche Vorzeichen besitzen. x
double Bisektion ( double a, double b, double eps ); //Überpruft zunächst, ob [a,b] eine Nullstelle enthält und verfährt dann nach der Bisektionsmethode. x
double MPRegel ( double a, double b, int N ); //Nähert das Integral von a bis b über f(x)dx an. x
int Sign( double a ); //Gibt das Vorzeichen von a aus (-1, 0, 1). x
double Read_double(std::string text);
int Read_int(std::string text);//Gibt text aus und liest einen int ein, welcher dann zurückgegeben wird.

int main ()
{
    double a1, b1, a2, b2;
    double eps;

    std::cout << "Einlesen des ersten Intervalls [a1,b1], was genau eine Nullstelle enthält.\n";
    a1 = Read_double("Geben Sie a1 ein.");
    b1 = Read_double("Geben Sie b1 ein.");

    std::cout << "Einlesen des zweiten Intervalls [a2,b2], was genau eine Nullstelle enthält.\n";
    a2 = Read_double("Geben Sie a2 ein.");
    b2 = Read_double("Geben Sie b2 ein.");

    eps = Read_double("Geben Sie die angestrebte Intervalllänge für die Bisektionsmethode ein.");

    std::cout << "Berechne Nullstellen... ";
    double n1, n2;
    n1 = Bisektion(a1, b1, eps);
    n2 = Bisektion(a2, b2, eps);
    std::cout << "Fertig! Weiter geht's.\n";

    int N;
    N = Read_int("Geben Sie die Anzahl der Rechtecke für die summierte Mittelpunktsregel ein.");
    std::cout << "Berechne die positive Fläche des Graphen...";
    double A = MPRegel(n1, n2, N);
    std::cout << "Fertig!\nDie Fläche lautet: " << A << " FE.\n";


}

double f ( double x )
{
    return std::exp(std::sin(x))-(x-1.0)*(x-6.0);
}

void Wertetabelle ( double a, double b, int N )
{
    double h = (b-a) / N;
    std::cout << "\nx\t\t\tf(x)\n-------------------\n";
    for ( int i = 0; i <= N; i++ )
    {
        std::cout << a + i*h << "   \t\t" << f(a + i*h) << std::endl;
    }
}

int Sign ( double a )
{
    if ( a < 0 )
        return -1;
    if ( a > 0 )
        return 1;
    return 0;
}

bool Einschluss ( double fa, double fb )
{
    if ( Sign(fa) != Sign(fb) )
        return true;
    return false;
}

double MPRegel ( double a, double b, int N )
{
    double h = (b-a)/N;
    double sum = 0;
    for ( int i = 1; i <= N; i++ )
    {
        sum += f( a + (i - 0.5)*h );
    }
    return h*sum;
}

double Bisektion ( double a, double b, double eps )
{
    double fa = 0;
    double fb = 0;
    double m = 0;
    double fm = 0;
    while ( b-a >= eps )
    {
        m = (a+b)/2;
        fa = f(a);
        fb = f(b);
        fm = f(m);

        if ( Einschluss(fa, fm) )
        {
            b = m;
        } else if ( Einschluss(fm, fb) )
        {
            a = m;
        } else {
            std::cout << "Fehler! Das betreffende Intervall besitzt keinen Einschluss!";
            return 0.0;
        }
    }

    return m;
}

double Read_double ( std::string text )
{
    std::cout << text << "\n (double): ";
    double ret;
    std::cin >> ret;
    return ret;
}

int Read_int ( std::string text )
{
    std::cout << text << "\n (int): ";
    double ret;
    std::cin >> ret;
    return ret;
}
