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
double Df ( double x ); //Implementiert Df.
void Wertetabelle ( double a, double b, int N ); //Gibt Argument und Funktionswert tabellarisch aus. x
bool Einschluss ( double fa, double fb ); //Überprüft, ob die beiden Argumente unterschiedliche Vorzeichen besitzen. x
double Newton ( double a, double b, double eps ); //Überpruft zunächst, ob [a,b] eine Nullstelle enthält und verfährt dann nach der Newtonsmethode. x
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

    eps = Read_double("Geben Sie das Epsilon für das Newtonverfahren ein.");

    std::cout << "Berechne Nullstellen... ";
    double n1, n2;
    n1 = Newton(a1, b1, eps);
    n2 = Newton(a2, b2, eps);
    std::cout << "Fertig! Weiter geht's.\n";

    int N;
    N = Read_int("GeBen Sie die Anzahl der Rechtecke für die summierte Mittelpunktsregel ein.");
    std::cout << "Berechne die positive Fläche des Graphen...";
    double A = MPRegel(n1, n2, N);
    std::cout << "Fertig!\nDie Fläche lautet: " << A << " FE.\n";


}

double f ( double x )
{
    return std::exp(std::sin(x))-(x-1.0)*(x-6.0);
}

double Df ( double x )
{
    return std::exp(std::sin(x))*std::cos(x)-2*x+7;
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

double Newton ( double a, double b, double eps )
{
    double x = (a+b)/2;
    double xold = 0;
    double fx = 0;
    double Dfx = 0;

    do {
        fx = f(x);
        Dfx = Df(x);

        xold = x;
        x = x - (fx)/(Dfx);
    } while ( std::abs(x-xold)>= eps or fx >= eps );

    return x;
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
